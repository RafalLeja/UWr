"""Generates random numbers with uniform distribution using os.urandom.
"""

import os

class Random:
    """Generate random numbers and count random bytes used.
    """

    def __init__(self):
        self._count = 0

    def random(self, n):
        """Generate a nonnegative random number less than n.

        The argument n should be positive, otherwise ValueError is raised.
        """
        if n <= 0:
            raise ValueError('argument of random() is not positive')
        nbits = n.bit_length()
        nbytes = (nbits + 7) // 8
        modulus = 2 ** nbits
        while True:
            b = os.urandom(nbytes)
            self._count += nbytes
            r = int.from_bytes(b, 'big') % modulus
            if r < n:
                return r

    def getCount(self):
        """Returns the number of random bytes read from os.urandom by this object.
        """
        return self._count
