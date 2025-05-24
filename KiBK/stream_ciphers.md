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
- How to generate the most **secure keystream**?


---

# WWII - Lorenz-Schlüsselmaschine Schlüssel-Zusatz 40
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/4/4d/Lorenz-SZ42-2.jpg/500px-Lorenz-SZ42-2.jpg" alt="Lorenz SZ40" width="450" style="float: right;"/>

- **Aka**: Lorenz SZ40 / Tunny
- used by the **German army** to encrypt RTTY messages
- **Synchronous** stream cipher

--- 
# WWII - Lorenz SZ40 building blocks
- **2 rotors**, each with **5 wheels**
- $\chi$ rotors: 41, 31, 29, 26, 23
- $\psi$ rotors: 43, 47, 51, 53, 59
- **2 motor wheels**: $\mu_{37}$, $\mu_{61}$
- **501+** "bit" key
- $\chi$ rotors shift every letter, $\psi$ rotors shifts depending on the $\mu$ wheels
- **Ciphertext**: $M_i \oplus \chi_i \oplus \psi_i = C_i, i \in \{0 ... 4\}$
---
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/4/4d/Lorenz-SZ42-2.jpg/500px-Lorenz-SZ42-2.jpg" alt="Lorenz SZ40" width="75%" style="float: right; margin-right: 13.5%;"/>

---
# WWII - Breaking the Lorenz SZ40
- **4000** characters of ciphertext were transmitted from **Athens** to **Vienna**
- the recipient asked (without encryption) for a **retransmission**,
- the sender ***retransmitted** the slightly shorter message, **without changing the key**
- the **British** intercepted both messages

---
# WWII - Breaking the Lorenz SZ40
- $P_1 \oplus K = C_1$
- $P_2 \oplus K = C_2$
- $C_1 \oplus C_2 = P_1 \oplus P_2$
- $C_1 \oplus C_2 \oplus P_1 = P_2$
- $C_1 \oplus P_1 = K$
---
# WWII - Breaking the Lorenz SZ40
- **Bill Tutte** noticed a 41-bit pattern in November 1941
- By **January 1942**, the complete logical structure of the machine was known
- The first programmable computer, **Colossus**, was built to decode the Lorenz cipher
- The first Lorenz machine was captured in **1945**

---

# Types of stream ciphers
## **Synchronous**: 
- the keystream is generated independently of the plaintext
- useless if 1 bit of keystream is lost
  
## **Self-synchronous**: 
- the keystream is generated from the previous ciphertext digits
- resistant to bit loss

---

# Modern stream ciphers - building blocks
- **Linear Feedback Shift Register (LFSR)**: a shift register with feedback
- **Fibbonacci LFSR**: a type of LFSR where the feedback is taken from multiple bits
<img src="https://upload.wikimedia.org/wikipedia/commons/2/28/LFSR-F16.svg" alt="LFSR" width="100%" style="float: right;"/>

---

# Modern stream ciphers - Fibonacci LFSR
- expressed as a polynomial mod 2
- $x^{16} + x^{14} + x^{13} + x^{11} + x^{0} = x^{0}$
- The longest period is $2^{16} - 1 = 65535$
- This period can archieved by using a **primitive polynomial** over the Galois field GF(2)
  - The number of taps must be **even**
  - The taps must be **co-prime**
  
---

# Modern stream ciphers - Galois LFSR
- Fibonacci LFSR cannot be **parallelized**
- The output is **the same** as with Fibonacci LFSR 
- One round takes **1 clock cycle**
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/d/d0/LFSR-G16.svg/590px-LFSR-G16.svg.png" alt="Galois LFSR" width="100%" style="float: right;"/>

---

# Non-linear feedback shift register (NLFSR)
- Safer than LFSR
- Uses a non-linear function to change the state
- We don't know how to build them...

---

# Non-linear combining functions (NLCF)
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/6/6b/Nonlinear-combo-generator.png/500px-Nonlinear-combo-generator.png" alt="NLCF" width="40%" style="float: right;"/>

- Fake a NLFSR
- Use a non-linear function to combine the bits of the LFSR

---

# Clock-controlled generators
- Now we shift, now we don't

---

# RC4
- Invented by **Ron Rivest** (**R** in **RSA**) in 1987
- Leaked in 1994
- Starts with a **key-scheduling algorithm (KSA)** to generate the initial state
- Then a **pseudo-random generation algorithm (PRGA)** is used to generate the keystream

--- 
# RC4 - Key-scheduling algorithm (KSA)
```python
for i from 0 to 255
    S[i] := i

j := 0
for i from 0 to 255
    j := (j + S[i] + key[i mod keylength]) mod 256
    swap values of S[i] and S[j]
```

---
# RC4 - Pseudo-random generation algorithm (PRGA)
```python
i := 0
j := 0
while GeneratingOutput:
    i := (i + 1) mod 256
    j := (j + S[i]) mod 256
    swap values of S[i] and S[j]
    t := (S[i] + S[j]) mod 256
    K := S[t]
    output K
```
---

# Use of RC4
- **WEP/WPA** (1997 - 2004)
- **SSL/TLS** (1999 - 2015)
- OpenBSD /dev/random (? - 2015)

---

# Problems with RC4
- **Biases** in the first bytes of the keystream
- No **initialization vector (IV)**, thus the same key produces the same keystream
- **Bit-flipping** attacks
- **7** diffrent attacks