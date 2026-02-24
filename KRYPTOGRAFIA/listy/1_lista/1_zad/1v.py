import sys
from itertools import cycle

alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
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


def index_of_coincidence(text):
    counts = {}
    for c in text:
        counts[c] = counts.get(c, 0) + 1
    total = len(text)
    if total < 2:
        return 0.0
    numerator = sum(cnt * (cnt - 1) for cnt in counts.values())
    denominator = total * (total - 1)
    return numerator / denominator


def find_key_length(ciphertext, max_len=25):
    best_ic = -1
    best_length = 2
    for l in range(2, max_len + 1):
        groups = [[] for _ in range(l)]
        for i, char in enumerate(ciphertext):
            group_index = i % l
            groups[group_index].append(char)
        total_ic = 0.0
        valid_groups = 0
        for group in groups:
            if len(group) < 2:
                continue
            group_text = "".join(group)
            ic = index_of_coincidence(group_text)
            total_ic += ic
            valid_groups += 1
        avg_ic = total_ic / valid_groups if valid_groups else 0.0
        current_diff = abs(avg_ic - 0.0667)
        best_diff = abs(best_ic - 0.0667) if best_ic != -1 else float("inf")
        if (avg_ic > best_ic) and (current_diff < best_diff):
            best_ic = avg_ic
            best_length = l
    return best_length


english_freq = {
    "A": 0.082,
    "B": 0.015,
    "C": 0.028,
    "D": 0.043,
    "E": 0.127,
    "F": 0.022,
    "G": 0.020,
    "H": 0.061,
    "I": 0.067,
    "J": 0.002,
    "K": 0.008,
    "L": 0.040,
    "M": 0.024,
    "N": 0.067,
    "O": 0.075,
    "P": 0.019,
    "Q": 0.001,
    "R": 0.059,
    "S": 0.063,
    "T": 0.091,
    "U": 0.028,
    "V": 0.010,
    "W": 0.024,
    "X": 0.002,
    "Y": 0.020,
    "Z": 0.001,
}


def find_shift(group):
    ciphertext_group = "".join(group)
    max_score = -1
    best_shift = 0
    for shift in range(26):
        decrypted = []
        for c in ciphertext_group:
            original = (ord(c) - ord("A") - shift) % 26
            decrypted.append(chr(original + ord("A")))
        score = 0.0
        total = len(decrypted)
        if total == 0:
            continue
        for char in decrypted:
            observed = decrypted.count(char) / total
            expected = english_freq.get(char, 0)
            score += (observed - expected) ** 2 / expected
        if score < max_score or max_score == -1:
            max_score = score
            best_shift = shift
    return best_shift


def find_key(ciphertext, key_length):
    groups = [[] for _ in range(key_length)]
    for i, char in enumerate(ciphertext):
        group_index = i % key_length
        groups[group_index].append(char)

    key = []
    for group in groups:
        shift = find_shift(group)
        key.append(chr(shift + ord("A")))

    key_str = "".join(key)
    return key_str


def main():
    ciphertext = sys.stdin.read().strip()
    ciphertext = "".join([c.upper() for c in ciphertext if c.isalpha()])

    key_length = find_key_length(ciphertext)
    print("Assumed Key Length:", key_length)

    key = find_key(ciphertext, key_length)
    print("Assumed Key:", key)

    decoded = decode(ciphertext, key)
    # decoded = []
    # for i, char in enumerate(ciphertext):
    #     shift = ord(key[i % key_length]) - ord("A")
    #     original = (ord(char) - ord("A") - shift) % 26
    #     decoded.append(chr(original + ord("A")))
    print("Decoded Text:", decoded)


if __name__ == "__main__":
    main()
