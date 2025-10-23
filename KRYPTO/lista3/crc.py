def crc(msg, chksum=0, bitlen=32, generator=0xEDB88320, flip=True):
    """Computes a CRC (defaults to zlib CRC-32) of a given message.

    This is the simplest, but not very efficient 'one bit at a time'
    version of the algorithm. `chksum` is the initial value of the
    checksum (allows for an incremental computation, and defaults to 0,
    meaning a fresh start), `bitlen` is the number of CRC bits (defaults
    to 32), `generator` is the generator polynomial in inverted form
    (since we process a byte starting from its LSB), and `flip` says
    if we need to flip all bits of the checksum at the beginning and the
    end of the computation.
    """
    mask = (1 << bitlen) - 1
    if flip:
        chksum ^= mask
    for b in msg:
        chksum ^= b
        for j in range(8):   # byte has 8 bits
            if chksum & 1:
                chksum >>= 1
                chksum ^= generator
            else:
                chksum >>= 1
    if flip:
        chksum ^= mask
    return chksum

if __name__ == '__main__':
    # a couple of tests comparing our crc to zlib.crc32
    import zlib, os, sys
    bad = []
    for i in range(100):
        if i < 10:   # sequences of length 0..9 of zeros
            lngth = i
            msg = bytes(lngth)
        elif i < 20: # sequences of length 1..10 of random bytes
            lngth = i-9
            msg = os.urandom(lngth)
        else:        # sequences of random length <= 65536 of random bytes
            lngth = int.from_bytes(os.urandom(2), sys.byteorder) + 1
            msg = os.urandom(lngth)
        mycrc = crc(msg)
        zlibcrc = zlib.crc32(msg)
        print('{:>3d} {:>6d} {:08X} {:08X}'.format(i+1, lngth, mycrc, zlibcrc),
              end=' ')
        if mycrc != zlibcrc:
            bad.append(i+1)
            print('BAD!')
        else:
            print('OK')
    if bad == []:
        print('Seems OK')
    else:
        print('Oops! These tests:', bad, 'failed!')

