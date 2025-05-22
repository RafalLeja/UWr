---
marp: true
title: Introduction to stream ciphers
theme: gradient
paginate: true
---

# Introduction to stream ciphers

- **What is a stream cipher?**
- **Brief history of streams and ciphers**
Let's dive in!

---

# What is a stream cipher?
A stream cipher is a symmetric key cipher where:
- **each** plaintext digit is encrypted **one at a time** with the corresponding digit of the **keystream**, to give a digit of the ciphertext stream. - Wikipedia
- **Keystream**: a sequence of bits used to encrypt plaintext

---

# 1553 - Vigenère cipher
- invented by **Blaise de Vigenère**
- shifts the plaintext by a **key** (a word)
- the key is **repeated** to match the length of the plaintext
```python
      h       e       l       l       o  message
   7 (h)   4 (e)  11 (l)  11 (l)  14 (o) message
+ 23 (X)  12 (M)   2 (C)  10 (K)  11 (L) key
= 30      16      13      21      25     message + key
=  4 (E)  16 (Q)  13 (N)  21 (V)  25 (Z) (message + key) mod 26
      E       Q       N       V       Z  → ciphertext
```
---

# 1553 - Vigenère cipher
- **Key**: a word, agreed upon by both parties
- **Vulnerable** to frequency analysis
- Not a modern stream cipher, but a **block cipher**

---

# 1882 - One-time-pad
- invented by **Frank Miller** to encrypt **telegraph messages**
<img src="https://upload.wikimedia.org/wikipedia/commons/4/4d/Frank_Miller_%281842-1925%29.png" alt="Frank Miller" width="350" style="float: right;"/>
- the only **unbreakable** cipher
- highly **impractical** due to key management

---

# 1882 - Modern one-time-pad
- **Key**: a random sequence of bits
- the stream is **XORed** with the key
- the key is **as long as** the plaintext
```
Message:     HELLO      → [01001000 01000101 01001100 01001100 01001111]
Key:         AGQZM      → [01100001 01000111 01010001 01011010 01001101]
Ciphertext:             → [00101001 00000010 00011101 00010110 00000010]
                        → [')'      \x02     \x1D     \x16     \x02   ] (bytes)
```
---

# Modern stream ciphers
- **Key**: a random sequence of bits
- The stream is **XORed** with the **keystream**
- The keystream is **generated** from the key
- The keystream is now **pseudo-random**, thus it's not **perfectly secure**

---

# Types of stream ciphers
- **Synchronous**: the keystream is generated independently of the plaintext
- **Self-synchronous**: the keystream is generated from the previous ciphertext digits
- **Asynchronous**: the keystream is generated from the previous plaintext digits

---

# WWII - Lorenz cipher