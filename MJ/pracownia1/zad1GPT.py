from transformers import pipeline

pipe = pipeline("text-generation", model="flax-community/papuGaPT2", device="cuda")

RUNNING = True

history = ""

while RUNNING:
    if history == "":
        input_text = input("Zadaj pytanie: " + history)
        history += ""
    else:
        input_text = input("> ")
    
    if input_text == "/exit":
        RUNNING = False
        break
    elif input_text == "/next":
        history = ""
        continue

    history += "Odpowiedź na pytanie '" + input_text + "' brzmi: \n"

    print("DEBUG=on============")
    print("HISTORIA: " + history, )
    print("DEBUG=off============")

    answer = pipe(history, max_new_tokens=100, truncation=False, return_full_text=False)[0]['generated_text']

    # print("DEBUG=on============")
    # print("ODP: " + answer)
    # print("DEBUG=off============")
 
    print("GPT: " + answer)
    # history += answer + "\n"

print("Goodbye!")
