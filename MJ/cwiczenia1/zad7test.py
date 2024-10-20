import torch
from transformers import AutoTokenizer, AutoModelForCausalLM, TextStreamer

model_name = "eryk-mazus/polka-1.1b-chat"

tokenizer = AutoTokenizer.from_pretrained(model_name, use_fast=True)
tokenizer.pad_token = tokenizer.eos_token

model = AutoModelForCausalLM.from_pretrained(
    model_name, 
    torch_dtype=torch.bfloat16 if torch.cuda.is_bf16_supported() else torch.float16,
    device_map="auto"
)
streamer = TextStreamer(tokenizer, skip_prompt=True)

