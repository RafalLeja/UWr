import hashlib
from random import randbytes

n_5 = 132976518568428873590990698990473888147434186684055790647542257711183504300793567894763258123494558264011608829984042495270894713938736746289613125052979025936004467648488790223063947335152106970185641201512558554026954048393654332511691849974991216693754764137851682541757604893914324078124535978192415120291
e_5 = 65537
d_5 = 90691539900408400794917546924290269291024396023883328113480877869245908291996431087663966131282119577132411918058451674796270519384770684482152644315318102571397196010481370395695226323681136902628494694117140916057608574759453391255173778818496321940136314911468520140003952162724505217290328347539832915473
c_5 = 32285987280270223193394300987555362945882719223146559544577770972899088517077123906704034961613752708098754728140271941658235688552502353529258875148446114782922280442774871977472579771277610967830632811877354856461374593809829697266148408396441603567328790550104677162545537524254825671420002401958272746803


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


sha_hash = Hash(hashlib.sha256)

print("Zad 5:")
# print(MGF1(sha_hash, b"seed", 64).hex())
m_5 = RSAES_OAEP_DECRYPT(
    Hash=sha_hash,
    MGF=MGF1,
    n=n_5,
    d=d_5,
    C=c_5.to_bytes((n_5.bit_length() + 7) // 8, byteorder="big"),
).decode()
print(m_5)

c_5p = RSAES_OAEP_ENCRYPT(
    Hash=sha_hash,
    MGF=MGF1,
    n=n_5,
    e=e_5,
    M=m_5.encode(),
).hex()
print(c_5p)

m_5p = RSAES_OAEP_DECRYPT(
    Hash=sha_hash,
    MGF=MGF1,
    n=n_5,
    d=d_5,
    C=bytes.fromhex(c_5p),
).decode()
print(m_5p)

print("Zad 6:")

n_6 = 71502864762146481719921706717489647274401371264339912861896668788523408898399987584458867427150377982863182827723210496949296670656691865361398662494882040185240162250557186910283675756901011497105524781775877739937033106782971695711279690633676059066099291799230305634094313871898669144926153021806765337119
e_6 = 2021535990211590963017392592316424966597438880474232111192775168758971118971196922496380667821335075997803106339714897610001405009507387105725190113425251075371250635294214688303728478757021436787448387590713186179971049230570754206241716782351576777192891629109675421410740010665647739359531488881247608893
c_6 = 60342465832449322744726634842148045802439244500089483738363609568925340232650344873572852511944450706598604355605661206516319914717158123597735277322179464919791400999160339273677529535935467512005475661904854431907925955377288727809206617991218845692977472510923562573590533382301718414219836335384794307181

for d in range(1000, 100000):
    print(f"d = {d}...")
    try:
        m_6 = RSAES_OAEP_DECRYPT(
            Hash=sha_hash,
            MGF=MGF1,
            n=n_6,
            # d=3,
            d=d,
            # d=65537,
            C=c_6.to_bytes((n_6.bit_length() + 7) // 8, byteorder="big"),
        ).decode()
    except ValueError:
        continue
    else:
        print(f"d = {d}")
        print(m_6)
        break
