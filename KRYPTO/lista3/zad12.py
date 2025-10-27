import pyUnicodeSteganography as usteg

encoded_text = open("./zad12.txt", "rb").read()
print(encoded_text[:5])
decodec_text = usteg.decode(encoded_text, method="lookalike", binary=True)
print(decodec_text)
