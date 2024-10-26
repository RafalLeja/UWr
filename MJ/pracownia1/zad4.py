import torch
from transformers import AutoTokenizer, AutoModelForCausalLM
from torch.nn import functional as F
import random
import pandas as pd
import time


model_name = 'eryk-mazus/polka-1.1b-chat'
device = 'cuda'
# device = 'cpu'

tokenizer = AutoTokenizer.from_pretrained(model_name, use_fast=True)
tokenizer.pad_token = tokenizer.eos_token

model = AutoModelForCausalLM.from_pretrained(
    model_name, 
    torch_dtype=torch.bfloat16 if torch.cuda.is_bf16_supported() else torch.float16,
    device_map="auto"
)

system_prompt = "Jesteś pomocnym asystentem. Odpowiadasz na pytania egzaminacyjne. Najlepiej odpowiadać jednym słowem."

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
    for q in typeQ.itertuples():
        chat.append({"role": "user", "content": q.question})
        chat.append({"role": "assistant", "content": correct.iloc[q.Index].answer})
    return chat


N_FEW = 3

for q in questions.itertuples():
    # print(q)
    chat = [{"role": "system", "content": system_prompt}]

    if "Czy" in q.question:
        chat = few_shots(binaryQ[:N_FEW])
        binaryQ = binaryQ.sample(frac=1)
    elif "Jak" in q.question:
        chat = few_shots(howQ[:N_FEW])
        howQ = howQ.sample(frac=1)
    elif "Ile" in q.question or "Ilu" in q.question:
        chat = few_shots(numQ[:N_FEW])
        numQ = numQ.sample(frac=1)
    elif "Kto" in q.question or "Któr" in q.question or "któr" in q.question:
        chat = few_shots(whoQ[:N_FEW])
        whoQ = whoQ.sample(frac=1)
    elif "Co" in q.question or "Czym" in q.question or "Czego" in q.question:
        chat = few_shots(whatQ[:N_FEW])
        whatQ = whatQ.sample(frac=1)
    else:
        chat = few_shots(restQ[:N_FEW])
        restQ = restQ.sample(frac=1)

    print(q.Index)

    chat.append({"role": "user", "content": q.question})
    inputs = tokenizer.apply_chat_template(chat, add_generation_prompt=True, return_tensors="pt")
    first_param_device = next(model.parameters()).device
    inputs = inputs.to(first_param_device)

    with torch.no_grad():
        outputs = model.generate(
            inputs,
            pad_token_id=tokenizer.eos_token_id,
            max_new_tokens=16,
            temperature=0.1,
            repetition_penalty=1.15,
            top_p=0.95,
            do_sample=True
        )

    new_tokens = outputs[0, inputs.size(1):]
    response = tokenizer.decode(new_tokens, skip_special_tokens=True)
    response = response.replace("\n", " ")
    print(response)
    # print(answer.split("\n")[1+(N_FEW*2)])
    outFile.write(response + "\n")

# print(sentence_prob(q))
# outFile.write(q + "\n")
# outFile.write(str(sentence_prob(q)) + "\n")
