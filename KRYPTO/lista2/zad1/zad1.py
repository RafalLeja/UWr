from Crypto.Cipher import AES

with open("./key", "rb") as keyF, open("./iv", "rb") as ivF:
    aes = AES.new(keyF.read(), AES.MODE_CBC, ivF.read())

    with open("./ciphertext", "rb") as cipherF:
        plaintext = aes.decrypt(cipherF.read())
        print(plaintext)

