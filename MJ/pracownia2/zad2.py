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

print(f'Uruchomiono na: {device}')

print(f'filtorwanie {tokenizer.vocab_size} tokenów')
suppress_tokeny = [t for t in tokeny[226:] if (
    t[0] == 'Ġ')]

suppress_indeksy = tokenizer.convert_tokens_to_ids(suppress_tokeny)

input_ids = tokenizer(prefiks, return_tensors='pt').to(device)

output = model.generate(**input_ids,
                        max_new_tokens=30,
                        do_sample=True,
                        eos_token_id=tokenizer.encode('.')[0],
                        pad_token_id=tokenizer.eos_token_id,
                        penalty_alpha=0.6,
                        repetition_penalty=1.8,
                        top_k=3,
                        top_p=0.92,
                        suppress_tokens=suppress_indeksy)
print(tokenizer.decode(output[0]))
# print(suppress_tokeny[:100])
