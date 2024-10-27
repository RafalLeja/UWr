import torch
from transformers import AutoModelForCausalLM, AutoTokenizer

model_name = "eryk-mazus/polka-1.1b"

tokenizer = AutoTokenizer.from_pretrained(model_name, padding_side="left")
tokenizer.pad_token = tokenizer.eos_token

model = AutoModelForCausalLM.from_pretrained(
    model_name, device_map="auto", load_in_8bit=True)

prompt = """Przykładowe zapytanie do modelu"""

model_inputs = tokenizer([prompt], return_tensors="pt").to("cuda")
with torch.no_grad():
    generated_ids = model.generate(
        **model_inputs,
        max_new_tokens=512,
        do_sample=True,
        penalty_alpha=0.6,
        top_k=5
    )

output = tokenizer.batch_decode(generated_ids, skip_special_tokens=True)[0]
print(output)
