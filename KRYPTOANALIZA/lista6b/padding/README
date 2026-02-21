Programs are placed in the top directory, modules — in the subdirectory rsa/.
All executables except mkPubRSAkey called with option -h print their help
messages. Modules provide some docstrings for the help() function.
All the documentation is summarized below.
------------------------------------------------------------------------
MODULES
------------------------------------------------------------------------
NAME
    rsa.rsa - Basic types and functions implementing the textbook RSA algorithm.

DESCRIPTION
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

CLASSES
    builtins.tuple(builtins.object)
        PrivRSAkey
        PubRSAkey

    class PrivRSAkey(builtins.tuple)
     |  PrivRSAkey(keyBits, keyBytes, n, e, p, q, d)
     |
     |  Static methods defined here:
     |  __new__(_cls, keyBits, keyBytes, n, e, p, q, d)
     |      Create new instance of PrivRSAkey(keyBits, keyBytes, n, e, p, q, d)
     |
     |  Data and other attributes defined here:
     |  
     |  _fields = ('keyBits', 'keyBytes', 'n', 'e', 'p', 'q', 'd')

    class PubRSAkey(builtins.tuple)
     |  PubRSAkey(keyBits, keyBytes, n, e)
     |
     |  Static methods defined here:
     |  
     |  __new__(_cls, keyBits, keyBytes, n, e)
     |      Create new instance of PubRSAkey(keyBits, keyBytes, n, e)
     |  
     |  Data and other attributes defined here:
     |  
     |  _fields = ('keyBits', 'keyBytes', 'n', 'e')

FUNCTIONS
    enc(m, key)
        Encrypts a message m with a given key.
        
        The message m should be an integer, the key should be of type
        PubRSAkey or PrivRSAkey.
    
    dec(c, key)
        Decrypts a ciphertext c with a given key.
        
        The ciphertext c should be an integer, the key should be of type
        PrivRSAkey.
    
    from_int(m, len=0)
        Converts an integer to a byte string.
        
        Optional parameter len specifies the length of the byte string.
        If len==0 the length is calculated automatically to fit the number m.

    to_int(b)
        Converts a byte string to a number.
    
    read(filename, keyType=<class 'rsa.rsa.PrivRSAkey'>)
        Reads an RSA key from a file named filename. Returns a named tuple
        of type keyType.
    
    write(key, filename)
        Writes an RSA key to a file named filename.

    sanityCheck(key)

------------------------------------------------------------------------
NAME
    rsa.pkcs15pad - Implementation of the PKCS#1 v. 1.5 RSA padding scheme.

DESCRIPTION
    References:
        B. Kaliski, PKCS #1: RSA Encryption Version 1.5, RFC 2313, March 1998.

CLASSES
    builtins.ValueError(builtins.Exception)
        PaddingError
    enum.Enum(builtins.object)
        ErrorCode
    
    class ErrorCode(enum.Enum)
     |  Indicates the cause of a padding error.
     |  
     |  Possible values:
     |      SUCCESS       – no error
     |      NO_DATA       – no plaintext found
     |      EMPTY_DATA    – empty plaintext
     |      DATA_TOO_BIG  – plaintext is too big
     |      ENC_TOO_SHORT – encoding is too short
     |      BAD_FRONT     – encoded string should start with 0x00
     |      BAD_BT        – block type BT should be equal to 0x02
     |      PAD_TOO_SHORT – padding is too short (should be at least 8 bytes)

    class PaddingError(builtins.ValueError)
     |  Raised with a parameter of type ErrorCode when there is an error
     |  during encoding or decoding.

FUNCTIONS
    dec(EB)
        Decode block EB and return its data.
    
    enc(D, k)
        Encode data D into a block of size k bytes.
------------------------------------------------------------------------
NAME
    rsa.oracle - Definition of the PKCS#1 v. 1.5 padding oracle.

CLASSES
    builtins.object
        Oracle
    
    class Oracle(builtins.object)
     |  Real PKCS#1 v. 1.5 padding oracle.
     |  
     |  This oracle answers the question whether the decryption of a given
     |  ciphertext is PKCS#1 v. 1.5 conforming.
     |  
     |  Methods defined here:
     |  
     |  __init__(self, key)
     |      Creates an oracle for a given private RSA key.
     |  
     |  count(self)
     |      Return the cumulative number of calls to the oracle.
     |  
     |  oracle(self, ciphertext)
     |      For a given ciphertext returns the padding error code of type ErrorCode.
     |      
     |      The enumeration ErrorCode is defined in module rsa.pkcs15pad.
     |  
     |  simpleOracle(self, ciphertext)
     |      This oracle answers the question wheather a0 <= m <= b0, where
     |         m = ciphertext ** d mod n (is the decryption of the ciphertext),
     |         a0 = 2*B,
     |         b0 = 3*B-1,
     |         B = 2**(8*(key.keyBytes-2)).
     |      Returns either ErrorCode.SUCCESS or ErrorCode.BAD_PREFIX.
     |      
     |      Note that it returns ErrorCode.SUCCESS much more often than the real
     |      oracle. If the real oracle returns ErrorCode.BAD_PREFIX, then obviously
     |      the ciphertext does not satisfy the inequalities a0 <= m <= b0.  But
     |      even if the ciphertext satisfies the inequalities, then the NO_DATA,
     |      PAD_TOO_SHORT or EMPTY_DATA errors may be returned (the last one is
     |      very improbable, though). The probablility of these other failures
     |      decreases when the key length increases.
------------------------------------------------------------------------
NAME
    rsa.primes - Implementation of the Miller-Rabin primality test.

FUNCTIONS
    isDivisible(n, primes)
        Checks wheter n is divisible by some element of the primes list.
        
        The argument primes shuld be a sorted list of all primes less than
        some bound.
    
    isPrime(n, primes, random, repetitions=10)
        Primality test based on Miller-Rabin algorithm.
        
        It first checks wheter n is divisible by a small prime (using isDivisible).
        If not, it repeats the Rabin-Miller primality test (using millerRabin) for
        randomly chosen parameters a ∈ [2,n-2]. The number of repetitions is limited
        by the fourth argument. Function random(k) should return random numbers
        less than k.
        
        The result is the number of iterations of the Miller-Rabin algorithm until
        the test failed or -1 if n passed all tests.
    
    millerRabin(a, n)
        The Miller-Rabin primality test for a given number n and parameter a.
------------------------------------------------------------------------
NAME
    rsa.findPrimeNextTo - Finds the smallest prime greater or equal to a given number.

FUNCTIONS
    findPrimeNextTo(n, testPrime)
        Finds the smallest prime greater or equal to n.
        
        testPrime should return the number of iterations of the Miller-Rabin
        algorithm until the test failed or -1 if n passed all tests.
------------------------------------------------------------------------
NAME
    rsa.getRandom - Generates random numbers with uniform distribution using os.urandom.

CLASSES
    builtins.object
        Random
    
    class Random(builtins.object)
     |  Generate random numbers and count random bytes used.
     |  
     |  Methods defined here:
     |  
     |  __init__(self)
     |  
     |  getCount(self)
     |      Returns the number of random bytes read from os.urandom by this object.
     |  
     |  random(self, n)
     |      Generate a nonnegative random number less than n.
     |      
     |      The argument n should be positive, otherwise ValueError is raised.
------------------------------------------------------------------------
NAME
    rsa.inverse - Computes x⁻¹ mod y.

DESCRIPTION
    Obsolete since Python 3.8, since pow now does the trick.

FUNCTIONS
    inv(x, y)
        Computes x⁻¹ mod y. With Python 3.8 or newer use pow(x, -1, y) instead.
        
        If x is not invertible modulo y, raises ValueError('not invertible').
------------------------------------------------------------------------
PROGRAMS
------------------------------------------------------------------------
genRSAkey:

Generates an RSA key.

Optional arguments (in given order):
    – name of a file to write the generated key to (default: RSAkey),
    – number of bits of the modulus n (default: 1024),
    – public exponent e (default: 65537).

The output file contains the following decimal numbers, each one in a separate
line:
    keyBits – number of bits of the modulus n,
    keyBytes – number of bytes of the modulus n,
    n — modulus, equal to p*q,
    e – public exponent (default: 65537),
    p — generated prime,
    q — generated prime,
    d – private exponent, equal to e⁻¹ mod (p-1)*(q-1).
First three lines of the output constitute the public key.

Primes are generated as follows: first a random number r is drawn. Then
consecutive odd numbers greater or equal to r are tested for primality. If a
tested number is divisible by a small prime, then '.' is printed. Otherwise if
it is rejected by a single invocation of the Miller-Rabin algorithm (with
randomly chosen a), then '!' is printed.  If more than one invocation of the
Miller-Rabin algorithm is performed on that number, then '*' is printed.
For p the number r is 2**(keyBits//2). Por q it is calculated to ensure
that p*q has exactly keyBits bits.
------------------------------------------------------------------------
mkPubRSAkey:

Converts a private RSA key into a public one.
------------------------------------------------------------------------
RSAkeySanity:

Performs some sanity checks on a private RSA key.

Optional argument:
    – name of a file containing the key (default: RSAkey).
------------------------------------------------------------------------
genSmallPrimes:

Creates a Python source file with a definition of a list of small primes.

Optional arguments to the program (in given order):
    – upper bound to which primes are calculated (default: 1000000),
    – name of the file to write the list to (default: smallPrimes.py).

The output file contains assignment statements defining the following
variables:
    bound – the upper bound,
    primes – the sorted list of all primes less than the upper bound.
------------------------------------------------------------------------
gen_bchbch:

Generate a ciphertext for the Bleichenbacher attack.

Optional parameters:
    – name of a file with a private RSA key (default: RSAkey),
    – name of a file with a plaintext (default: plain.txt).
    – name of a file with a ciphertext (default: cipher.txt).
------------------------------------------------------------------------
