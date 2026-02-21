import hashlib

def hash(s):
    m = hashlib.sha256()
    m.update(s)
    return m.digest()

def xor3(u,v,w):
    return bytes(map(lambda u, v, w: u^v^w, u, v, w))

a =    b'FOO-0x000000003B1BD2039' + b' ' * 53 + bytes.fromhex('dd3ff46f')
b =    b'BAR-0x00000000307238E22' + b' ' * 53 + bytes.fromhex('a80da323')
c = b'FOOBAR-0x000000001BB6C4C9F' + b' ' * 50 + bytes.fromhex('b01d7c21')

xyz = map(hash, (a,b,c))
uvw = map(hash, xyz)
xor3uvw = xor3(*uvw)

print(xor3uvw.hex())
