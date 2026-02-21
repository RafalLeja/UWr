import hashlib
from fractions import Fraction
from math import isqrt
from random import randbytes

n = 71502864762146481719921706717489647274401371264339912861896668788523408898399987584458867427150377982863182827723210496949296670656691865361398662494882040185240162250557186910283675756901011497105524781775877739937033106782971695711279690633676059066099291799230305634094313871898669144926153021806765337119

e = 2021535990211590963017392592316424966597438880474232111192775168758971118971196922496380667821335075997803106339714897610001405009507387105725190113425251075371250635294214688303728478757021436787448387590713186179971049230570754206241716782351576777192891629109675421410740010665647739359531488881247608893

c = 60342465832449322744726634842148045802439244500089483738363609568925340232650344873572852511944450706598604355605661206516319914717158123597735277322179464919791400999160339273677529535935467512005475661904854431907925955377288727809206617991218845692977472510923562573590533382301718414219836335384794307181


class Hash:
    def __init__(self, hashlib_func):
        self.hashlib_func = hashlib_func
        self.digest_size = hashlib_func().digest_size

    def __call__(self, data: bytes):
        hasher = self.hashlib_func()
        hasher.update(data)
        return hasher.digest()


# def sha_hash(m: int) -> int:
#     sha = hashlib.sha256()
#     sha.update(m.to_bytes((m.bit_length() + 7) // 8, byteorder="big"))
#     return int.from_bytes(sha.digest(), byteorder="big")


def MGF1(Hash, mgfSeed: bytes, maskLen: int) -> bytes:
    hLen = Hash.digest_size
    if maskLen > (2**32) * hLen:
        raise ValueError("mask too long")
    T = b""
    for counter in range(0, -(-maskLen // hLen)):  # ceil(maskLen / hLen)
        C = counter.to_bytes(4, byteorder="big")
        T += Hash(mgfSeed + C)
    return T[:maskLen]


def RSAES_OAEP_ENCRYPT(Hash, MGF, n: int, e: int, M: bytes, L: bytes = b""):
    k = (n.bit_length() + 7) // 8  # length in bytes of modulus n
    hLen = Hash.digest_size

    # 1. Length checking
    if len(L) * 8 > 2 ** (hLen * 4):
        raise ValueError("label too long")

    if len(M) > k - 2 * hLen - 2:
        raise ValueError("message too long")

    # 2. EME-OAEP encoding
    lHash = Hash(L)
    PS = b"\x00" * (k - len(M) - 2 * hLen - 2)
    DB = lHash + PS + b"\x01" + M
    seed = randbytes(hLen)
    dbMask = MGF(Hash, seed, len(DB))
    maskedDB = bytes(x ^ y for x, y in zip(DB, dbMask))
    seedMask = MGF(Hash, maskedDB, hLen)
    maskedSeed = bytes(x ^ y for x, y in zip(seed, seedMask))
    EM = b"\x00" + maskedSeed + maskedDB

    # 3. RSA encryption
    m = int.from_bytes(EM, byteorder="big")
    c = pow(m, e, n)
    C = c.to_bytes(k, byteorder="big")

    # 4. Output
    return C


def RSAES_OAEP_DECRYPT(Hash, MGF, n: int, d: int, C: bytes, L: bytes = b""):
    k = (n.bit_length() + 7) // 8  # length in bytes of modulus n
    hLen = Hash.digest_size

    # 1. Length checking
    if len(L) * 8 > 2 ** (hLen * 4):
        raise ValueError("decryption error")
    if len(C) != k:
        raise ValueError("decryption error")
    if k < 2 * hLen + 2:
        raise ValueError("decryption error")

    # 2. RSA decryption
    c = int.from_bytes(C, byteorder="big")
    m = pow(c, d, n)
    EM = m.to_bytes(k, byteorder="big")

    # 3. EME-OAEP decoding
    lHash = Hash(L)
    Y = EM[0]
    maskedSeed = EM[1 : 1 + hLen]
    maskedDB = EM[1 + hLen :]

    seedMask = MGF(Hash, maskedDB, hLen)
    seed = bytes(x ^ y for x, y in zip(maskedSeed, seedMask))
    dbMask = MGF(Hash, seed, k - hLen - 1)
    DB = bytes(x ^ y for x, y in zip(maskedDB, dbMask))

    lHash_p = DB[:hLen]
    if lHash != lHash_p or Y != 0:
        raise ValueError("decryption error")

    # Find the position of the 0x01 byte
    try:
        index = DB.index(b"\x01", hLen)
    except ValueError:
        raise ValueError("decryption error")

    M = DB[index + 1 :]

    # 4. Output
    return M


def check_c(n, phi):
    a = 1
    b = -(n - phi + 1)
    delta = (b**2) - (4 * a * n)
    if delta < 0:
        return -1, -1
    x1 = (-b + isqrt(delta)) // (2 * a)
    x2 = (-b - isqrt(delta)) // (2 * a)
    return x1, x2


def unravel_en(e, n):
    frac = Fraction(e, n)
    en = frac

    p2, p1 = 0, 1
    q2, q1 = 1, 0
    while frac.numerator != 0:
        a = frac.__floor__()
        if frac - a == 0:
            break
        frac = 1 / (frac - a)
        p = a * p1 + p2
        q = a * q1 + q2
        # print(f"Current convergent: {p}/{q}")

        if p != 0:
            # if p > 0 and frac - en > 0 and q % 2 == 1:
            # c = Fraction((e * q) - 1, p)
            # if c.denominator == 1:
            phi = (e * q - 1) // p
            x1, x2 = check_c(n, phi)
            if x1.is_integer() and x2.is_integer() and x1 * x2 == n:
                return int(x1), int(x2)

        p2, p1 = p1, p
        q2, q1 = q1, q
    return 0, 0


sha_hash = Hash(hashlib.sha256)

p, q = unravel_en(e, n)
print(p, q)
d = pow(e, -1, (p - 1) * (q - 1))

m = RSAES_OAEP_DECRYPT(
    Hash=sha_hash,
    MGF=MGF1,
    n=n,
    d=d,
    C=c.to_bytes((n.bit_length() + 7) // 8, byteorder="big"),
).decode()
print(m)
