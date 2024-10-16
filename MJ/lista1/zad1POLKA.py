from transformers import pipeline

# pipe = pipeline("text-generation", model="eryk-mazus/polka-1.1b", device="cuda")
pipe = pipeline("text-generation", model="eryk-mazus/polka-1.1b")

RUNNING = True

TEMPLATE = "[INST] Jesteś ekspetrem od literatury. Odpowiadasz na pytania dotyczące książek i ich autorów. [/INST]\n"

history = TEMPLATE

while RUNNING:
    if history == TEMPLATE:
        input_text = input("Zadaj pytanie: ")
    else:
        input_text = input("> ")

    if input_text == "/exit":
        RUNNING = False
        break
    elif input_text == "/next":
        history = ""
        continue

    history += "[INST] " + input_text + " [/INST]\n"

    print("DEBUG=on============")
    print("HISTORIA: " + history, )
    print("DEBUG=off============")

    answer = pipe(history, max_new_tokens=100, truncation=True,
                  return_full_text=False)[0]['generated_text']

    # print("DEBUG=on============")
    # print("ODP: " + answer)
    # print("DEBUG=off============")

    print("POLKA: " + answer)
    history += answer + "\n"

print("Goodbye!")
