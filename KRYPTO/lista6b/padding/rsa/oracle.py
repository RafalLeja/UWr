""" Definition of the PKCS#1 v. 1.5 padding oracle.
"""

import rsa.rsa as rsa
import rsa.pkcs15pad as pad

class Oracle:
    """Real PKCS#1 v. 1.5 padding oracle.

    This oracle answers the question wheather the decryption of a given
    ciphertext is PKCS#1 v. 1.5 conforming.
    """

    def __init__(self, key):
        """Creates an oracle for a given private RSA key.
        """
        self.key = key
        self._count = 0

    def oracle(self, ciphertext):
        """For a given ciphertext returns the padding error code of type ErrorCode.

        The enumeration ErrorCode is defined in module rsa.pkcs15pad.
        """
        def decrypt(ciphertext):
            return pad.dec(rsa.from_int((rsa.dec(ciphertext, self.key)),
                self.key.keyBytes))
        self._count += 1
        try:
            decrypt(ciphertext)
            return pad.ErrorCode.SUCCESS
        except pad.PaddingError as err:
            return err.args[0]

    def simpleOracle(self, ciphertext):
        """This oracle answers the question whether a0 <= m <= b0, where
           m = ciphertext ** d mod n (is the decryption of the ciphertext),
           a0 = 2*B,
           b0 = 3*B-1,
           B = 2**(8*(key.keyBytes-2)).
        Returns either ErrorCode.SUCCESS or ErrorCode.BAD_PREFIX.

        Note that it returns ErrorCode.SUCCESS much more often than the real
        oracle. If the real oracle returns ErrorCode.BAD_PREFIX, then obviously
        the ciphertext does not satisfy the inequalities a0 <= m <= b0.  But
        even if the ciphertext satisfies the inequalities, then the NO_DATA,
        PAD_TOO_SHORT or EMPTY_DATA errors may be returned (the last one is
        very improbable, though). The probablility of these other failures
        decreases when the key length increases.
        """
        if self.oracle(ciphertext) != pad.ErrorCode.BAD_PREFIX:
            return pad.ErrorCode.SUCCESS
        else:
            return pad.ErrorCode.BAD_PREFIX

    def count(self):
        """Return the cumulative number of calls to the oracle.
        """
        return self._count
