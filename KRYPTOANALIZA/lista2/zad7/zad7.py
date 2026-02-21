from binascii import hexlify
from random import randbytes, randrange, seed

from Crypto.Cipher import AES

# seed(3)

# moneta = 1
moneta = randrange(0, 2, 1)
print(f"Adam wybrał {'AES' if moneta == 1 else 'losową permutację'}")

key = randbytes(16)

N = randrange(0, 2**16, 2)
print(f"N = {N}")

M = 6
print(f"M = {M}")


def Adam(p):
    if moneta:
        o = bytearray(0)
        for iv in range(N, N + len(p) // 16):
            aes = AES.new(key, AES.MODE_CBC, iv.to_bytes(16, "big"))

            tmp = aes.encrypt(p[(iv - N) * 16: (iv - N + 1) * 16])

            o += tmp
        return o
    else:
        o = bytearray(0)
        for iv in range(N, N + len(p) // 16):
            aes = AES.new(key, AES.MODE_CBC, iv.to_bytes(16, "big"))
            o += aes.encrypt(randbytes(16))
        return o


p = bytearray()
X = [randrange(0, 2, 1) for _ in range(M)]
print(f"x = {''.join(map(str, X))}")
for x in X:
    if x == 1:
        p += bytearray(16)
        p += int(1).to_bytes(16, "big")
    else:
        p += bytearray(32)

for i in range(len(p) // 16):
    print(f"p{i} = {hexlify(p[i * 16: (i + 1) * 16])}")

c = Adam(p)
for i in range(len(p) // 16):
    print(f"c{i} = {hexlify(c[i * 16: (i + 1) * 16])}")

y = []
for i in range((len(p) // 16) // 2):
    a = 2 * i
    b = 2 * i + 1
    if c[a * 16: b * 16] == c[b * 16: (b + 1) * 16]:
        y += [1]
    else:
        y += [0]

print(f"y = {''.join(map(str, y))}")
print(f"x = {''.join(map(str, X))}")
print(f"Bob zgaduje: {'AES' if X == y else 'losowa permutacja'}")
