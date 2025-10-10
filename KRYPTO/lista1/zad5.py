from itertools import cycle,product 

alphabet = 'AĄBCĆDEĘFGHIJKLŁMNŃOÓPQRSŚTUVWXYZŻŹ'
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

def findFragment(ciphertext, plaintext_fragment):
    for i in range(len(ciphertext) - len(plaintext_fragment)):
        print(calculateKey(
            ciphertext[i:i+len(plaintext_fragment)],
            plaintext_fragment
        ))

def nextKey():
    length = 1
    while True:
        for combo in product(alphabet, repeat=length):
            yield "".join(combo)
        length += 1


def bruteforce(ciphertext, plaintext_fragment):
    plaintext = ""
    key_gen = nextKey()
    key = ""
    while plaintext_fragment not in plaintext:
        key = next(key_gen)
        print(f" trying key: {key}")
        plaintext = decode(ciphertext, key)
        print(plaintext)
        key = nextKey()

    print(f"found key: {key}")
    print(decode(ciphertext, key))


bruteforce(
"""ŃABQYĆVLHĄOHQKĆNVODGQVŹŁFIXDWUJOZQNXŃNMRHZŹVSUJDFCWUFKRYĘSUÓLIWZEĆFHĄZNŚĘRKN\
YRZXCSIKQKĘVZZSHAMĆULNBSHJTÓHINQDOWŹKŁGSDATFŹCJDNMYAABCWXQOŻKĘYXTCXŹGZQMĆBZI\
ĘZEXSŃLĄFŹPDVNYNVŹZCIOFSQŻZKGAPXÓŁRUŃŃIQRUÓŁNZSYHQPBLIMŻAOPĄWLNBCEŚXSZĄÓOCUA\
ZXTXCUJUĆIHĄNAGGIUNMBCBDXRQLOBIQOBYPIPZXXĘZĘONOTŹQIULUXHRNAKSHBŹĘTFXWZSĘĘÓBV\
IBJRAÓĘWWQŹZEĆDTNŹNŚ""", "KULTURY")
