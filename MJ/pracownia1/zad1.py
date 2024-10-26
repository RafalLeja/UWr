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
# streamer = TextStreamer(tokenizer, skip_prompt=True)

system_prompt = "Jesteś pomocnym asystentem. Podpowiadasz użytkownikowi, co ma jeść. Użytkownik chce utrzymać zdrową dietę."
chat = [{"role": "system", "content": system_prompt}]

while True:
    user_input = input("Zadaj pytanie: ")
    if user_input == "exit":
        break
    if user_input == "new":
        chat = [{"role": "system", "content": system_prompt}]
        continue
    chat.append({"role": "user", "content": user_input})

    inputs = tokenizer.apply_chat_template(chat, add_generation_prompt=True, return_tensors="pt")
    first_param_device = next(model.parameters()).device
    inputs = inputs.to(first_param_device)

    with torch.no_grad():
        output1 = model.generate(
            inputs,
            pad_token_id=tokenizer.eos_token_id,
            max_new_tokens=256,
            temperature=0.1,
            repetition_penalty=1.15,
            top_p=0.95,
            do_sample=True
        )
        output2 = model.generate(
            inputs,
            pad_token_id=tokenizer.eos_token_id,
            max_new_tokens=256,
            temperature=0.2,
            repetition_penalty=1.15,
            top_p=0.95,
            do_sample=True
        )
        output3 = model.generate(
            inputs,
            pad_token_id=tokenizer.eos_token_id,
            max_new_tokens=256,
            temperature=0.3,
            repetition_penalty=1.15,
            top_p=0.95,
            do_sample=True
        )

    outputs = min(output1, output2, output3, key=lambda x: x.size(1))
    new_tokens = outputs[0, inputs.size(1):]
    response = tokenizer.decode(new_tokens, skip_special_tokens=True)
    print("Odpowiedź: ", response)
    chat.append({"role": "assistant", "content": response})