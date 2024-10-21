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

system_prompt = "Jesteś tłumaczem. Tłumaczysz z angielskiego na polski."
chat = [{"role": "system", "content": system_prompt}]

# user_input = "Przetłumacz podane zdanie 'Where is the nearest bus stop?' na polski."
user_input = "Przetłumacz podane zdanie 'I have a red car' na polski."

chat.append({"role": "user", "content": user_input})

inputs = tokenizer.apply_chat_template(chat, add_generation_prompt=True, return_tensors="pt")

with torch.no_grad():
    outputs = model.generate(
        inputs,
        pad_token_id=tokenizer.eos_token_id,
        max_new_tokens=512,
        temperature=0.2,
        repetition_penalty=1.15,
        top_p=0.95,
        do_sample=True,
        streamer=streamer,
    )

new_tokens = outputs[0, inputs.size(1):]
response = tokenizer.decode(new_tokens, skip_special_tokens=True)
print(response)
# chat.append({"role": "assistant", "content": response})