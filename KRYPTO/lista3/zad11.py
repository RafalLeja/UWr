import hashlib
from itertools import combinations


def hash(s):
    m = hashlib.sha256()
    m.update(s.encode("utf-8"))
    return m.digest()


text = open("./zad11.txt", "r", encoding="utf-8").read()
lines = text.split("\n")
print(lines)
originalHash = hash(text)

print("originalHash", originalHash.hex())


def modify(idx):
    outlines = lines.copy()
    for i in idx:
        outlines[i] += " "

    return "\n".join(outlines)


possibleIdx = set(range(len(lines))) - set(
    [1, 2, 5, 7, 9, 12, 13, 14, 15, 16, 17, 19, 20]
)

bruteHash = 0b0
for i in range(14, len(lines)):
    print(f"trying i = {i}")
    for j in combinations(possibleIdx, i):
        # print(f"trying {j}")
        bruteText = modify(j)
        bruteHash = hash(bruteText)
        if bruteHash.hex().startswith("000000"):
            print("bruteHash", bruteHash.hex())
            with open("zad11Fake.txt", "w") as outfile:
                outfile.write(bruteText)
                exit()

print("imposible")
