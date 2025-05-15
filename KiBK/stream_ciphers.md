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

# 1882 - One-time-pad
- invented by **Frank Miller** to encrypt **telegraph messages**
- the stream is **XORed** with the key
- the key is **as long as** the plaintext
- the only **unbreakable** cipher
- highly **impractical** due to key management
- **Key**: a random sequence of bits