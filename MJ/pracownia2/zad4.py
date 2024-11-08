import torch
from transformers import AutoTokenizer, AutoModelForCausalLM
from torch.nn import functional as F
import pandas as pd
import random


model_name = 'flax-community/papuGaPT2'

device = 'cuda' if torch.cuda.is_available() else 'cpu'

tokenizer = AutoTokenizer.from_pretrained(model_name)
model = AutoModelForCausalLM.from_pretrained(model_name).to(device)

indeksy = list(range(tokenizer.vocab_size))
tokeny = tokenizer.convert_ids_to_tokens(indeksy)

prefiksy = pd.read_csv('prefiksy.txt', header=None, sep='\t')
prefiksy = prefiksy.sample(frac=1)
prefiks = prefiksy.iloc[0, 0]

print(f'Uruchomiono na: {device}')
print(f'Prefiks: {prefiks}')

litera = prefiks[0].lower()

print(f'filtorwanie "{litera}*" na {tokenizer.vocab_size} tokenów')
suppress_tokeny = [t for t in tokeny[226:] if (
    t[0] == 'Ġ' and t[1].lower() != litera)]

suppress_indeksy = tokenizer.convert_tokens_to_ids(suppress_tokeny)

input_ids = tokenizer(prefiks, return_tensors='pt').to(device)

outputs = []
OPTS = 4
for i in range(OPTS):
    output = model.generate(**input_ids,
                            max_new_tokens=30,
                            do_sample=True,
                            eos_token_id=tokenizer.encode('.')[0],
                            pad_token_id=tokenizer.eos_token_id,
                            penalty_alpha=0.6,
                            repetition_penalty=1.8,
                            top_k=5,
                            top_p=0.92,
                            suppress_tokens=suppress_indeksy)
    outputs.append(tokenizer.decode(output[0]))


max_len = 0
max_opt = ""
for i in range(OPTS):
    lengths = [len(w) for w in outputs[i].split(' ')]
    if sum(lengths) > max_len:
        max_len = sum(lengths)
        max_opt = outputs[i]

print(max_opt)
# print(suppress_tokeny[:100])
