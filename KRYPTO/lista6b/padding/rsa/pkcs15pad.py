"""Implementation of the PKCS#1 v. 1.5 RSA padding scheme.

References:
    B. Kaliski, PKCS #1: RSA Encryption Version 1.5, RFC 2313, March 1998.
"""

import os
import enum

class PaddingError(ValueError):
    """Raised with a parameter of type ErrorCode when there is an error
    during encoding or decoding.
    """
    pass

class ErrorCode(enum.Enum):
    """Indicates the cause of a padding error.

    Possible values:
        SUCCESS       – no error
        NO_DATA       – no plaintext found
        EMPTY_DATA    – empty plaintext
        DATA_TOO_BIG  – plaintext is too big
        ENC_TOO_SHORT – encoding is too short
        BAD_FRONT     – encoded string should start with 0x00
        BAD_BT        – block type BT should be equal to 0x02
        PAD_TOO_SHORT – padding is too short (should be at least 8 bytes)
    """

    SUCCESS       = 0
    NO_DATA       = 1
    EMPTY_DATA    = 2
    DATA_TOO_BIG  = 3
    ENC_TOO_SHORT = 4
    BAD_PREFIX    = 5
    PAD_TOO_SHORT = 6

def enc(D, k):
    """Encode data D into a block of size k bytes.
    """
    k0 = len(D)
    if k0 == 0:
        raise PaddingError(ErrorCode.EMPTY_DATA)
    if k < k0 + 11:
        raise PaddingError(ErrorCode.DATA_TOO_BIG)
    BT = b'\x02'
    PS = bytearray()
    for i in range(k - k0 - 3):
        PSi = os.urandom(1)
        while PSi[0] == 0:
            PSi = os.urandom(1)
        PS.append(PSi[0])
    return b'\x00' + BT + PS + b'\x00' + D

def dec(EB):
    """Decode block EB and return its data.
    """
    if len(EB) < 12:
        raise PaddingError(ErrorCode.ENC_TOO_SHORT)
    BT = 0x02
    if EB[0] != 0x0:
        raise PaddingError(ErrorCode.BAD_PREFIX)
    if EB[1] != BT:
        raise PaddingError(ErrorCode.BAD_PREFIX)
    for i in range(2, 10):
        if EB[i] == 0:
            raise PaddingError(ErrorCode.PAD_TOO_SHORT)
    for i in range(10, len(EB)):
        if EB[i] == 0:
            break
    else:
        raise PaddingError(ErrorCode.NO_DATA)
    i += 1
    if i == len(EB):
        raise PaddingError(ErrorCode.EMPTY_DATA)
    return EB[i:]
