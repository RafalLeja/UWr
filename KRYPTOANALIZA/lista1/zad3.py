from itertools import cycle
import random

random.seed()
alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
alphalen = len(alphabet)
num2char = dict(enumerate(alphabet))
char2num = { num2char[n]:n for n in num2char }

def encodeChar(c, k):
    return num2char[(char2num[c]+char2num[k]) % alphalen]

def decodeChar(c, k):
    return num2char[(char2num[c]-char2num[k]) % alphalen]

def encode(plaintext, key):
    return ''.join(map(encodeChar, plaintext, cycle(key)))

def decode(ciphertext, key):
    return ''.join(map(decodeChar, ciphertext, cycle(key)))

def calculateKey(ciphertext, plaintext):
    return ''.join([num2char[(char2num[c]-char2num[s]) % alphalen] for c, s in zip(ciphertext, plaintext)])

print("Zadanie 3")

real_msg = 'LADUNKISAPODLOZONE'
print(f"prawdziwa wiadomość: {real_msg}")

real_key = ''.join([num2char[random.randrange(0, alphalen)] for _ in real_msg]).upper()
print(f"wylosowany klucz: {real_key}")

ciphertext = encode(real_msg, real_key)
print(f"zaszyfrowana wiadomość: {ciphertext}")
print("---------")

fake_msg = 'NIELUBIEDYKTATORKI'
print(f"fałszywa wiadomość: {fake_msg}")

fake_key = calculateKey(ciphertext, fake_msg)
print(f"fałszywy klucz: {fake_key}")

fake_ciphertext = encode(fake_msg, fake_key)
print(f"zaszyfrowana fałszywa wiadomość: {fake_ciphertext}")

