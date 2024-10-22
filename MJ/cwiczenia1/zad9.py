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
    input_ids = tokenizer(sentence_txt, return_tensors='pt')[
        'input_ids'].to(device)
    with torch.no_grad():
        output = model(input_ids=input_ids)
        log_probs = log_probs_from_logits(
            output.logits[:, :-1, :], input_ids[:, 1:])
        seq_log_probs = torch.sum(log_probs)
    return seq_log_probs.cpu().numpy()


sentences = [
    'To jest zwykłe polskie zdanie.',
    'This is a normal English sentence.',
    'iweryuiiu hrfw3eieur fr',
    'Rano poszedłem po bułki do sklepu',
    'Wczoraj wieczorem spotkałem pewną wspaniałą kobietę, która z pasją opowiadała o modelach językowych.'
]

zdanie = sentences[3]
# zdanie = input("Podaj zdanie: ")
slowa = zdanie.split()
pierwsze = slowa[0]
ostatnie = slowa[-1]
slowa = slowa[1:-1]
random.shuffle(slowa)

#####################

print("input = ", slowa)


def partiton(lst):
    n = len(lst)
    n = n//2
    return lst[:n], lst[n:]


def merge(lst1, lst2):
    sen = ""
    i = 0
    j = 0
    lst1 = lst1.strip().split(" ")
    lst2 = lst2.strip().split(" ")
    while i < len(lst1) and j < len(lst2):
        if sentence_prob(sen + lst1[i] + " " + lst2[j]) > sentence_prob(sen + lst2[j] + " " + lst1[i]):
            sen += lst1[i] + " "
            i += 1
        else:
            sen += lst2[j] + " "
            j += 1

    if i < len(lst1):
        sen += " " + " ".join(lst1[i:])

    if j < len(lst2):
        sen += " " + " ".join(lst2[j:])

    return sen


def qprobsort(lst):
    if len(lst) == 1:
        return lst[0]

    left, right = partiton(lst)
    out = merge(qprobsort(left), qprobsort(right))
    print(out)
    return out


print(pierwsze + " " + qprobsort(slowa) + " " + ostatnie)
