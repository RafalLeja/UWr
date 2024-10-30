import torch
from transformers import AutoModelForCausalLM, AutoTokenizer
import random
import time

DEVICE = "cuda" if torch.cuda.is_available() else "cpu"

model_name = "eryk-mazus/polka-1.1b"

tokenizer = AutoTokenizer.from_pretrained(model_name, padding_side="left")
tokenizer.pad_token = tokenizer.eos_token

model = AutoModelForCausalLM.from_pretrained(
    model_name, device_map="auto")
