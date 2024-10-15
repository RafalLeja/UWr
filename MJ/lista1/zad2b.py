import torch
from transformers import AutoTokenizer, AutoModelForCausalLM
from torch.nn import functional as F
import random
import itertools

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
    
# sentences = [
#   'To jest zwykłe polskie zdanie.',
#   'This is a normal English sentence.',
#   'iweryuiiu hrfw3eieur fr' ,
#   'Wczoraj wieczorem spotkałem pewną wspaniałą kobietę, która z pasją opowiadała o modelach językowych.'   
# ]

zdanie = input("Podaj zdanie: ")
slowa = zdanie.split()
pierwsze = slowa[0]
ostatnie = slowa[-1]
slowa = slowa[1:-1]
random.shuffle(slowa)

pairs = []
probabilities = []
for s1 in slowa:
    for s2 in slowa:
        if s1 != s2:
            zdanie = s1 + " " + s2
            pairs.append((s1, s2))
            probabilities.append(sentence_prob(zdanie))

pairs = [x for _, x in sorted(zip(probabilities, pairs), reverse=True)]
probabilities.sort(reverse=True)

new_pairs = []
i = 0
while i < len(pairs):
    s1, s2 = pairs[i]
    new_pairs.append((s1, s2))
    # pairs = list(filter(lambda x:  not (x[0] != s1 and x[1] != s2), pairs))
    pairs = list(filter(lambda x:  x[0] != s1, pairs))
    pairs = list(filter(lambda x:  x[1] != s1, pairs))
    pairs = list(filter(lambda x:  x[0] != s2, pairs))
    pairs = list(filter(lambda x:  x[1] != s2, pairs))

    # pairs = list(filter(lambda x:  not (x[0] != s1 and x[1] != s2), pairs))
    i += 1

pairs = new_pairs

for pair, prob in zip(pairs, probabilities):
    print(pair, prob)

# order = []
# order.append(pierwsze)
# i = 0
# while len(slowa) > 0:
#     s1 = order[i]
#     print(s1)
#     max_val = -100000
#     max_word = ""
#     for s2 in slowa:
#         if s1 != s2:
#             zdanie = s1 + " " + s2
#             score = sentence_prob(zdanie)
#             if score > max_val:
#                 max_val = score
#                 max_word = s2
#     order.append(max_word)
#     slowa.remove(max_word)
#     i += 1

# print(" ".join(order))

# #####################

# random.shuffle(slowa)
# def partiton(lst):
#     n = len(lst)
#     n = n//2
#     return lst[:n], lst[n:]

# def qprobsort(lst):
#     if len(lst) == 2:
#         if sentence_prob(" ".join(lst)) > sentence_prob(" ".join(lst[::-1])):
#             return " ".join(lst)
#         else:
#             return " ".join(lst[::-1])
#     elif len(lst) == 1:
#         return lst[0]

#     left, right = partiton(lst)
#     return qprobsort(left) + " " + qprobsort(right)

# print(pierwsze + " " + qprobsort(slowa) + " " + ostatnie)
    