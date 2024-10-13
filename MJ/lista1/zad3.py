import torch
from transformers import AutoTokenizer, AutoModelForCausalLM
from torch.nn import functional as F
import random
import itertools
import pandas as pd


model_name = 'flax-community/papuGaPT2'
# device = 'cuda'
device = 'cpu'

tokenizer = AutoTokenizer.from_pretrained(model_name)
model = AutoModelForCausalLM.from_pretrained(model_name).to(device)

def log_probs_from_logits(logits, labels):
    logp = F.log_softmax(logits, dim=-1)
    logp_label = torch.gather(logp, 2, labels.unsqueeze(2)).squeeze(-1)
    return logp_label
    
            
def sentence_prob(sentence_txt):
    input_ids = tokenizer(sentence_txt, return_tensors='pt')['input_ids'].to(device)
    with torch.no_grad():
        output = model(input_ids=input_ids)
        log_probs = log_probs_from_logits(output.logits[:, :-1, :], input_ids[:, 1:])
        seq_log_probs = torch.sum(log_probs)
    return seq_log_probs.cpu().numpy()  

DEBUG = False
N = 400

reviews = pd.read_csv("reviews.txt", sep="#", header=None, names=["sentiment", "review"], encoding="utf-8")
shuffled = reviews.sample(frac=1)

poprawne = 0
for row in shuffled[:N].itertuples():
    zdanieP = "\"" + row.review + "\": jest opinią pozytywną."
    zdanieN = "\"" + row.review + "\": jest opinią negatywną."
    probP = sentence_prob(zdanieP)
    probN = sentence_prob(zdanieN)
    if probP > probN and row.sentiment == "GOOD":
        poprawne += 1
    elif row.sentiment == "BAD":
        poprawne += 1
    elif not DEBUG:
        # print(row.review)
        print(zdanieP, probP)
        print(zdanieN, probN)
        print(row.sentiment)
        print("===")

    if DEBUG:
        # print(row.review)
        print(zdanieP, probP)
        print(zdanieN, probN)
        print(row.sentiment)
        print("===")

print("Poprawne: ", poprawne, " na ", N)

