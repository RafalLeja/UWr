"""Basic types and functions implementing the textbook RSA algorithm.

This module provides the definition of named tuples PubRSAkey and PrivRSAkey.
PrivRSAkey contains the following fields:
    keyBits – number of bits of the modulus n,
    keyBytes – number of bytes of the modulus n,
    n — modulus, should be equal to p*q,
    e – public exponent,
    p — generated prime,
    q — generated prime,
    d – private exponent, should be equal to e⁻¹ mod n.
PubRSAkey contains the first four fields listed above.

Functions read and write allow to read/store a key from/to a file.
Key fields are written as decimal integers in separate lines of a file.

A simple sanity check is also provided as a separate function.

Functions enc and dec provide the RSA encryption and decryption.

Functions from_int and to_int convert between integers and byte strings.
"""

import collections

PubRSAkey = collections.namedtuple('PubRSAkey', ('keyBits','keyBytes', 'n', 'e'))
PrivRSAkey = collections.namedtuple('PrivRSAkey', PubRSAkey._fields
    + ('p', 'q', 'd'))

def read(filename, keyType=PrivRSAkey):
    """Reads an RSA key from a file named filename. Returns a named tuple
    of type keyType.
    """
    def readNumbers(keyFile):
        for line in keyFile:
            yield int(line.strip())
    with open(filename) as keyFile:
        return keyType._make(readNumbers(keyFile))

def write(key, filename):
    """Writes an RSA key to a file named filename.
    """
    with open(filename, 'w') as output:
        print(*key, sep='\n', file=output)

def sanityCheck(key):
    return key.p*key.q == key.n and (key.d*key.e)%((key.p-1)*(key.q-1)) == 1

def enc(m, key):
    """Encrypts a message m with a given key.

    The message m should be an integer, the key should be of type
    PubRSAkey or PrivRSAkey.
    """
    return pow(m, key.e, key.n)

def dec(c, key):
    """Decrypts a ciphertext c with a given key.

    The ciphertext c should be an integer, the key should be of type PrivRSAkey.
    """
    return pow(c, key.d, key.n)

def to_int(b):
    """Converts a byte string to a number.
    """
    return int.from_bytes(b, 'big')

def from_int(m, len=0):
    """Converts an integer to a byte string.

    Optional parameter len specifies the length of the byte string.
    If len==0 the length is calculated automatically to fit the number m.
    """
    return m.to_bytes(len if len>0 else (m.bit_length()+7)//8, 'big')
