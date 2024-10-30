import torch
from transformers import AutoTokenizer, AutoModelForCausalLM
from torch.nn import functional as F
import random

model_name = 'flax-community/papuGaPT2'
device = 'cuda' if torch.cuda.is_available() else 'cpu'

tokenizer = AutoTokenizer.from_pretrained(model_name)
model = AutoModelForCausalLM.from_pretrained(model_name).to(device)


def log_probs_from_logits(logits, labels):
    logp = F.log_softmax(logits, dim=-1)
    logp_label = torch.gather(logp, 2, labels.unsqueeze(2)).squeeze(-1)
    return logp_label


def sentence_prob(sentence_txt):
    input_ids = tokenizer(sentence_txt, return_tensors='pt')[
        'input_ids'].to(device)
    length = input_ids.size(1)
    with torch.no_grad():
        output = model(input_ids=input_ids)
        log_probs = log_probs_from_logits(
            output.logits[:, :-1, :], input_ids[:, 1:])
        seq_log_probs = torch.sum(log_probs)
    return seq_log_probs.cpu().numpy().item()


options = "wprost|wyprosty|wyprostu|wyprost uwielbiała|wielbił|wielbiła|uwielbił|wielbiło|uwielbiał|uwielbiało|uwielbiały słuchać|osłuchać|słychać|usłuchać o|i|e|a|ó|ę|y|ą|u wartościach własnych|owłosionych macierzy|mocarz|macierzą|macierze|mocarza|mocarze|mocarzy|macierz"
options = [x.split('|') for x in options.split(' ')]

BEAM_SIZE = 2

beams = [(x, sentence_prob(x)) for x in options[0]]
beams = sorted(beams, key=lambda x: x[1], reverse=True)
beams = beams[:BEAM_SIZE]
for depth in range(1, len(options)):
    variations = options[depth]
    print("depth", depth)
    # print(beams)
    new_beams = []
    for i, beam in enumerate(beams):
        print(f'Processing beam {i+1}/{len(beams)}')
        best = []
        for variation in variations:
            sentence = beam[0] + ' ' + variation
            prob = sentence_prob(sentence)
            best.append((sentence, prob))
        best = sorted(best, key=lambda x: x[1], reverse=True)
        best = best[:BEAM_SIZE]
        new_beams.extend(best)
    beams = new_beams

beams = sorted(beams, key=lambda x: x[1], reverse=True)
correct_sentence = " ".join([o[0] for o in options])

[print(b) for b in beams]
# beams = [b[0].split(' ') for b in beams]
print("zdanie właściwe = ", correct_sentence)


index = [i for i, beam in enumerate(beams) if beam[0] == correct_sentence]
if len(index) == 0:
    print("Nie znaleziono poprawnego zdania")
else:
    print(index)
