import asn1
from math import gcd

with open("key.der", "rb") as f:
    decoder = asn1.Decoder()
    decoder.start(f)
    tag, value = decoder.read()
    # print(tag)
    # print(value)

ver, n, e, d, p, q, dp, dq, qinv = value

print(f"1. n = p * q: {p * q == n}")
phi = (p - 1) * (q - 1)
psi = phi // gcd(p - 1, q - 1)
print(f"2. d = e^(-1) (mod p - 1 * q - 1): {pow(e, -1, phi) == d}")
print(f"2. d = e^(-1) (mod lcm(p - 1, q - 1)): {pow(e, -1, psi) == d}")
print(f"3. dp ≡ e^-1 (mod p - 1): {dp == pow(e, -1, p - 1)}")
print(f"4. dq ≡ e^-1 (mod q - 1): {dq == pow(e, -1, q - 1)}")
print(f"5. qinv ≡ q^(-1) (mod p): {qinv == pow(q, -1, p)}")


def int2str(n):
    return int2bytes(n).decode()


def int2bytes(n):
    return n.to_bytes((n.bit_length() + 7) // 8, "big")


def bytes2int(b):
    return int.from_bytes(b, "big")


def str2int(s):
    return bytes2int(s.encode())


c = 0x59DC3B0327E09B6B762385AC3FA1724A5C3761338018C1C69D691D563BE751377119397A86BD0873B9DD4259B94CDC7398FECBE9C252A4EF682BB09C17AFAD343E4C38F264B12ABFFF5AEF54F830A08B8C30E334BBD94A003310B5678A238135B1B89C324246129A6D8FCC34AA18386444AE3BF1D4BB7ADB603DA50B44683E024E32DCEE966531D1204D34A4CD51CF53431ACB3044588A4DE8CA124154308F557796873763FD625767B4296266E2C7CE07F891B8C6716DEB78DE0B84C6883FC42633A6CEEE2B4118E3C105C55DE092A61FBCA5CC4EC1F9A29C45A688D18D49AE5296363668E30C611E4ECBAACDFC4AF9458110A80ECAB25A6E2B19745271C1BE
# c = str2int(cipher)
m = pow(c, d, n)
print(f"Decrypted message: {int2str(m)}")
print("""A Method for Obtaining Digital Signatures and Public-Key Cryptosystems
R.L. Rivest, A. Shamir, and L. Adleman∗""")
