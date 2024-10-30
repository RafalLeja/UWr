import torch
from transformers import AutoTokenizer, AutoModelForCausalLM
from torch.nn import functional as F
import random


model_name = 'flax-community/papuGaPT2'

device = 'cuda' if torch.cuda.is_available() else 'cpu'

tokenizer = AutoTokenizer.from_pretrained(model_name)
model = AutoModelForCausalLM.from_pretrained(model_name).to(device)


def best_k(prefix, K=10):
    input_ids = tokenizer(prefix, return_tensors='pt')['input_ids'].to(device)
    output = model(input_ids=input_ids)
    next_token_logits = output.logits[0, -1, :]
    probs = F.softmax(next_token_logits, dim=-1)
    d = {}
    for i in range(probs.shape[0]):
        d[tokenizer.decode(i)] = probs[i]

    return [(t, d[t]) for t in sorted(d, key=d.get, reverse=True)[:K]]


def sample_from_pairs(pairs):
    tokens = [p[0] for p in pairs]
    weights = [p[1] for p in pairs]
    return random.choices(tokens, weights=weights, k=1)[0]


def sample_demo(N, txt):
    for i in range(N):
        d = best_k(txt)
        print(txt)
        next_token = sample_from_pairs(d)
        for t, p in best_k(txt):
            star = ''
            if t == next_token:
                star = '*'
            print(f'   [{t}]{star} {p:.4f}')
        txt += next_token
        print()


print(best_k("wprost"))
