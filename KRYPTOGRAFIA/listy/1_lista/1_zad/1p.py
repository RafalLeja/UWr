import sys

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

# mapping = {"W": "F"}
mapping = {"F": "w", "C": "e", "Z": "h", "N": "l"}
reverse_mapping = {v: k for k, v in mapping.items()}


def frequency_analysis(ciphertext):
    counts = {}
    total = 0
    for c in ciphertext:
        counts[c] = counts.get(c, 0) + 1
        total += 1

    freqs = {c: count / total for c, count in counts.items()}
    return freqs


def bigram_analysis(ciphertext):
    counts = {}
    total = 0
    for c1, c2 in zip(ciphertext, ciphertext[1:]):
        bigram = c1 + c2
        if c1 != c2:
            continue
        counts[bigram] = counts.get(bigram, 0) + 1
        total += 1
    freqs = {b: count / total for b, count in counts.items()}
    return freqs


def trigram_analysis(ciphertext):
    counts = {}
    total = 0
    for c1, c2, c3 in zip(ciphertext, ciphertext[1:], ciphertext[2:]):
        trigram = c1 + c2 + c3
        counts[trigram] = counts.get(trigram, 0) + 1
        total += 1
    freqs = {t: count / total for t, count in counts.items()}
    return freqs


def main():
    ciphertext = sys.stdin.read().strip()
    ciphertext = "".join([c.upper() for c in ciphertext if c.isalpha()])
    sorted_freqs = sorted(
        frequency_analysis(ciphertext).items(),
        key=lambda x: x[1],
        reverse=True,
    )
    sorted_english_freq = sorted(english_freq.items(), key=lambda x: x[1], reverse=True)
    print("Character frequencies in the ciphertext:")
    for c, e in zip(sorted_freqs, sorted_english_freq):
        print(f"{c[0]}: {c[1]:.4f} (English: {e[0]}: {e[1]:.4f})")

    sorted_bigrams = sorted(
        bigram_analysis(ciphertext).items(), key=lambda x: x[1], reverse=True
    )
    print("Most common bigrams in the ciphertext:")
    for b, f in sorted_bigrams[:10]:
        print(f"{b}: {f:.4f}")

    sorted_trigrams = sorted(
        trigram_analysis(ciphertext).items(), key=lambda x: x[1], reverse=True
    )
    print("Most common trigrams in the ciphertext:")
    for t, f in sorted_trigrams[:10]:
        print(f"{t}: {f:.4f}")

    decrypted = []
    for c in ciphertext:
        m = mapping.get(c, c)
        decrypted.append(m)
    print("Decrypted text (using mapping):")
    print("".join(decrypted))


if __name__ == "__main__":
    main()
