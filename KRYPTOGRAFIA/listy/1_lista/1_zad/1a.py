import sys
from math import sqrt


def extended_gcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = extended_gcd(b % a, a)
        return (g, x - (b // a) * y, y)


def modinv(a, m):
    g, x, y = extended_gcd(a, m)
    if g != 1:
        return None
    else:
        return x % m


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


def decrypt(ciphertext, a, b):
    inv_a = modinv(a, 26)
    if inv_a is None:
        return ""
    decrypted = []
    for c in ciphertext:
        if not c.isalpha():
            decrypted.append(c)
            continue
        x = ord(c.upper()) - ord("A")
        y = (inv_a * (x - b)) % 26
        decrypted_char = chr(y + ord("A"))
        decrypted.append(decrypted_char)
    return "".join(decrypted)


def chi_squared(text):
    observed = {}
    total_letters = 0
    for c in text:
        if c.isalpha():
            upper_c = c.upper()
            observed[upper_c] = observed.get(upper_c, 0) + 1
            total_letters += 1
    chi_sum = 0.0
    for char in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
        expected_count = english_freq[char] * total_letters
        observed_count = observed.get(char, 0)
        if expected_count == 0:
            continue
        chi_sum += (observed_count - expected_count) ** 2 / expected_count
    return chi_sum


def main():
    ciphertext = sys.stdin.read().strip()
    min_chi = float("inf")
    best_text = ""
    best_key = (0, 0)
    valid_a = [1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25]

    for a in valid_a:
        inv_a = modinv(a, 26)
        if inv_a is None:
            continue
        for b in range(0, 26):
            decrypted_text = decrypt(ciphertext, a, b)
            current_chi = chi_squared(decrypted_text)
            if current_chi < min_chi:
                min_chi = current_chi
                best_text = decrypted_text
                best_key = (a, b)
    print("Best decrypted text:")
    print(best_text)
    print(f"Key (a, b): {best_key}")


if __name__ == "__main__":
    main()
