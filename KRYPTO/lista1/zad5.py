from itertools import cycle, product
import queue

alphabet = "AĄBCĆDEĘFGHIJKLŁMNŃOÓPQRSŚTUVWXYZŻŹ"
alphalen = len(alphabet)
num2char = dict(enumerate(alphabet))
char2num = {num2char[n]: n for n in num2char}


def encodeChar(c, k):
    return num2char[(char2num[c] + char2num[k]) % alphalen]


def decodeChar(c, k):
    return num2char[(char2num[c] - char2num[k]) % alphalen]


def encode(plaintext, key):
    return "".join(map(encodeChar, plaintext, cycle(key)))


def decode(ciphertext, key):
    return "".join(map(decodeChar, ciphertext, cycle(key)))


def calculateKey(ciphertext, plaintext):
    return "".join(
        [
            num2char[(char2num[c] - char2num[s]) % alphalen]
            for c, s in zip(ciphertext, plaintext)
        ]
    )


def findFragment(ciphertext, plaintext_fragment):
    for i in range(len(ciphertext) - len(plaintext_fragment)):
        print(
            calculateKey(
                ciphertext[i : i + len(plaintext_fragment)], plaintext_fragment
            )
        )


def nextKey():
    length = 1
    while True:
        for combo in product(alphabet, repeat=length):
            yield "".join(combo)
        length += 1


def leftShift(text, n):
    return text[n:] + text[:n]


def rightShift(text, n):
    return text[-n:] + text[:-n]


def bruteforce(ciphertext, plaintext_fragment):
    key_candidates = queue.Queue()
    [key_candidates.put(num2char[k]) for k in range(alphalen)]
    while not key_candidates.empty():
        key = key_candidates.get()
        # print(f"trying {key}")
        if encode(plaintext_fragment, key) in ciphertext:
            i = ciphertext.index(encode(plaintext_fragment, key)) % len(key)

            print(f"key: {rightShift(key, i)}")
            print(f"plaintext: {decode(ciphertext, rightShift(key, i))}")

        if (
            len(key) <= len(plaintext_fragment)
            and encode(plaintext_fragment[: len(key)], key) in ciphertext
        ):
            [key_candidates.put(key + num2char[k]) for k in range(alphalen)]


bruteforce(
    """ŃABQYĆVLHĄOHQKĆNVODGQVŹŁFIXDWUJOZQNXŃNMRHZŹVSUJDFCWUFKRYĘSUÓLIWZEĆFHĄZNŚĘRKN\
YRZXCSIKQKĘVZZSHAMĆULNBSHJTÓHINQDOWŹKŁGSDATFŹCJDNMYAABCWXQOŻKĘYXTCXŹGZQMĆBZI\
ĘZEXSŃLĄFŹPDVNYNVŹZCIOFSQŻZKGAPXÓŁRUŃŃIQRUÓŁNZSYHQPBLIMŻAOPĄWLNBCEŚXSZĄÓOCUA\
ZXTXCUJUĆIHĄNAGGIUNMBCBDXRQLOBIQOBYPIPZXXĘZĘONOTŹQIULUXHRNAKSHBŹĘTFXWZSĘĘÓBV\
IBJRAÓĘWWQŹZEĆDTNŹNŚ""",
    "KULTURY",
)
