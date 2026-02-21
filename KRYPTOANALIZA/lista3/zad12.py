encoded_text = open("./zad12.txt", "r").read()

ones = "BZINoOPTaBeoOpcTy"
zeros = "ΒΖΙΝοΟΡΤаВеоОрсТу"
twos = ""

blacklist = "!(),.:;ąćęłńóśŚżŻ"

decoded_text = ""
for i in list(encoded_text):
    if i in blacklist:
        continue
    elif i in zeros:
        decoded_text += "1"
    elif i in ones:
        decoded_text += "0"

print(decoded_text)
