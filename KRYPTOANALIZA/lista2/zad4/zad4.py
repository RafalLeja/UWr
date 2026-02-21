from Crypto.Cipher import AES
from random import randrange, randbytes, seed
from binascii import hexlify

# seed(3)

# moneta = 1
moneta = randrange(0, 2, 1)
print(f"Adam wybrał {'AES' if moneta == 1 else 'losową permutację'}")
key = randbytes(16)

pamAdam = {}


def Adam(iv, p1, p2):
    if moneta:
        aes = AES.new(key, AES.MODE_CBC, iv)
        o1 = aes.encrypt(p1)
        o2 = aes.encrypt(p2)
        return (o1, o2)
    else:
        if (str(p1), str(p2)) not in pamAdam:
            o1 = randbytes(16)
            o2 = randbytes(16)
            pamAdam[str(p1), str(p2)] = (o1, o2)
        return pamAdam[str(p1), str(p2)]
        if (str(iv), str(p1), str(p2)) not in pamAdam:
            o1 = randbytes(16)
            o2 = randbytes(16)
            pamAdam[str(iv), str(p1), str(p2)] = (o1, o2)
        return pamAdam[str(iv), str(p1), str(p2)]


print("Wersja 1")
c1, c2 = Adam(bytearray([0] * 16), bytearray([0] * 16), bytearray([0] * 16))
print(f"IV = 0, p1 = 0, p2 = 0 => {hexlify(c1)}, {hexlify(c2)}")
c1p, c2p = Adam(c1, bytearray([0] * 16), bytearray([0] * 16))
print(f"IV = c1, p1 = 0, p2 = 0 => {hexlify(c1p)}, {hexlify(c2p)}")

print(f"Bob zgaduje: {'AES' if c1p == c2 else 'losowa permutacja'}")

print("Wersja 2")


def AdamE(iv, p1, p2):
    if moneta:
        helpAes = AES.new(key, AES.MODE_CBC, bytearray([0] * 16))
        aes = AES.new(key, AES.MODE_CBC, helpAes.encrypt(iv))
        o1 = aes.encrypt(p1)
        o2 = aes.encrypt(p2)
        return (o1, o2)
    else:
        if (str(p1), str(p2)) not in pamAdam:
            o1 = randbytes(16)
            o2 = randbytes(16)
            pamAdam[str(p1), str(p2)] = (o1, o2)
        return pamAdam[str(p1), str(p2)]
        if (str(iv), str(p1), str(p2)) not in pamAdam:
            o1 = randbytes(16)
            o2 = randbytes(16)
            pamAdam[str(iv), str(p1), str(p2)] = (o1, o2)
        return pamAdam[str(iv), str(p1), str(p2)]


c1, c2 = AdamE(bytearray([0] * 16), bytearray([0] * 16), bytearray([0] * 16))
print(f"IV = 0, p1 = 0, p2 = 0 => {hexlify(c1)}, {hexlify(c2)}")

c1p, c2p = AdamE(bytearray([0] * 16), bytearray([0] * 16), c1)
print(f"IV = 0, p1 = 0, p2 = c1 => {hexlify(c1p)}, {hexlify(c2p)}")

c1b, c2b = AdamE(c2p, bytearray([0] * 16), c2)
print(f"IV = c1p, p1 = 0, p2 = c2 => {hexlify(c1b)}, {hexlify(c2b)}")

print(f"Bob zgaduje: {'AES' if c1b ==
      c2 and c2b == c2p else 'losowa permutacja'}")
