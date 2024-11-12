from transformers import AutoTokenizer, AutoModelForCausalLM

modelName = "flax-community/papuGaPT2"

tokenizer = AutoTokenizer.from_pretrained(modelName)
model = AutoModelForCausalLM.from_pretrained(modelName)

prefiksy = ["Ala ma ", "Litwo, ojczyzno moja, ty jesteś jak ", "W Szczebrzeszynie chrząszcz brzmi w ",
            "Jabłko jest koloru ", "Woda jest mokra, a ogień ", "Kot ma cztery "]


suffiksy = []
s_suffiksy = []

for prefiks in prefiksy:
    input = tokenizer(prefiks[:-1], return_tensors="pt")
    output = model.generate(
        input['input_ids'], max_length=20, num_return_sequences=1, pad_token_id=tokenizer.eos_token_id, eos_token_id=tokenizer.eos_token_id)
    suffiksy.append(tokenizer.decode(output[0], skip_special_tokens=True))

    input = tokenizer(prefiks, return_tensors="pt")
    output = model.generate(
        input['input_ids'], max_length=20, num_return_sequences=1, pad_token_id=tokenizer.eos_token_id, eos_token_id=tokenizer.eos_token_id)
    s_suffiksy.append(tokenizer.decode(output[0], skip_special_tokes=True))

print("Prefiksy:")
for i in range(len(prefiksy)):
    print(prefiksy[i])
    print(suffiksy[i])
    print(s_suffiksy[i])
