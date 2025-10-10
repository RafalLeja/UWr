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

def bruteforce(ciphertext):
    for letter in list(alphabet):
        print(f"{letter}: {decode(ciphertext, letter)}")

def guess(ciphertext, seed):
    key_hint = ''.join([num2char[(char2num[c]-char2num[s]) % alphalen] for c, s in zip(ciphertext, seed)])
    print(f"key fragment : {key_hint}")
    print("Input key: ")
    key = input().upper()
    print(f"plaintext: {decode(ciphertext, key)}")

print("Zadanie 4")
print("podpunkt 1:\n")
bruteforce("FDGEFYQUMYMODKBFASDMBTQD")

print("podpunkt 2:\n")
guess("XHQPMFTFSJBHAMEHGIGHISHLPHLJAECWRVSRJWXNQECBSIQSCQSRHERWTWSVLVMRVLJAECWRVSRJWXNQECBSIFIHCPKS", "ITMAY")
