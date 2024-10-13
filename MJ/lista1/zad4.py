import torch
from transformers import AutoTokenizer, AutoModelForCausalLM
from torch.nn import functional as F
import random
import pandas as pd
import time


model_name = 'eryk-mazus/polka-1.1b'
# device = 'cuda'
device = 'cpu'

tokenizer = AutoTokenizer.from_pretrained(model_name)
model = AutoModelForCausalLM.from_pretrained(model_name).to(device)


def log_probs_from_logits(logits, labels):
    logp = F.log_softmax(logits, dim=-1)
    logp_label = torch.gather(logp, 2, labels.unsqueeze(2)).squeeze(-1)
    return logp_label


def sentence_prob(sentence_txt):
    input_ids = tokenizer(sentence_txt, return_tensors='pt')[
        'input_ids'].to(device)
    with torch.no_grad():
        output = model(input_ids=input_ids)
        log_probs = log_probs_from_logits(
            output.logits[:, :-1, :], input_ids[:, 1:])
        seq_log_probs = torch.sum(log_probs)
    return seq_log_probs.cpu().numpy()


questions = pd.read_csv("pytania.txt",
                        sep="#",
                        header=None,
                        names=["question"],
                        encoding="utf-8")


# binary = questions.filter(regex="/Czy", axis=0)
binaryQ = questions[questions['question'].str.contains("Czy", na=True)]
restQ = questions[~questions['question'].str.contains("Czy", na=True)]

howQ = restQ[restQ['question'].str.contains("Jak", na=True)]
restQ = restQ[~restQ['question'].str.contains("Jak", na=True)]

numQ = restQ[restQ['question'].str.contains(
    "Ile|Ilu", na=True)]
restQ = restQ[~restQ['question'].str.contains("Ile|Ilu", na=True)]

whoQ = restQ[restQ['question'].str.contains(
    "Kto|Któr|któr", na=True)]
restQ = restQ[~restQ['question'].str.contains(
    "Kto|Któr|któr", na=True)]

whatQ = restQ[restQ['question'].str.contains(
    "Co | Czym | Czego", na=True)]
restQ = restQ[~restQ['question'].str.contains(
    "Co | Czym | Czego", na=True)]

correct = pd.read_csv("correct_answers.txt",
                      sep="#",
                      header=None,
                      names=['answer'],
                      encoding="utf-8")

# print(binaryQ[:10])
# print(howQ[:10])
# print(numQ[:10])
# print(whoQ[:10])
# print(whatQ[:10])
# print(restQ[:10])

# print(len(binaryQ) + len(howQ) + len(numQ) +
#       len(whoQ) + len(whatQ) + len(restQ))

outFile = open("found_answers.txt", "w", encoding="utf-8")

random.seed(time.time())

binaryQ = binaryQ.sample(frac=1)
howQ = howQ.sample(frac=1)
numQ = numQ.sample(frac=1)
whoQ = whoQ.sample(frac=1)
whatQ = whatQ.sample(frac=1)
restQ = restQ.sample(frac=1)


def few_shots(typeQ):
    out = ""
    for q in typeQ.itertuples():
        out += "[INST] " + q.question + " [/INST]\n" + \
            correct.loc[q.Index].answer + "\n"
    return out


N_FEW = 2

for q in questions.itertuples():
    # print(q)
    few = ""
    if "Czy" in q.question:
        few = few_shots(binaryQ[:N_FEW])
    elif "Jak" in q.question:
        few = few_shots(howQ[:N_FEW])
    elif "Ile" in q.question or "Ilu" in q.question:
        few = few_shots(numQ[:N_FEW])
    elif "Kto" in q.question or "Któr" in q.question or "któr" in q.question:
        few = few_shots(whoQ[:N_FEW])
    elif "Co" in q.question or "Czym" in q.question or "Czego" in q.question:
        few = few_shots(whatQ[:N_FEW])
    else:
        few = few_shots(restQ[:N_FEW])

    querry = few + "[INST] " + q.question + " [/INST]\n"
    print(querry)
    input = tokenizer(querry, return_tensors='pt')
    attention_mask = input["attention_mask"]
    output = model.generate(
        input["input_ids"],
        max_new_tokens=50,
        num_return_sequences=1,
        pad_token_id=tokenizer.eos_token_id)
    answer = tokenizer.decode(
        output[0], skip_special_tokens=True).split("\n")[-1]
    print(answer)
    outFile.write(answer + "\n")

    # print(sentence_prob(q))
    # outFile.write(q + "\n")
    # outFile.write(str(sentence_prob(q)) + "\n")
