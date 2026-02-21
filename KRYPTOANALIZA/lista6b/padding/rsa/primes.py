"""Implementation of the Miller-Rabin primality test.
"""

import itertools

def isDivisible(n, primes):
    """Checks wheter n is divisible by some element of the primes list.
    
    The argument primes shuld be a sorted list of all primes less than
    some bound.
    """
    for p in itertools.takewhile(lambda p: p*p<=n, primes):
        if n % p == 0:
            return True
    return False

def millerRabin(a, n):
    """The Miller-Rabin primality test for a given number n and parameter a.
    """
    def extractTwos(m):
        s = 0
        while True:
            (m1, r) = divmod(m, 2)
            if r != 0:
                break
            m = m1
            s += 1
        return (s, m)

    (s, d) = extractTwos(n-1)
    if pow(a, d, n) == 1:
        return True
    for r in range(0, s):
        if pow(a, d, n) == n-1:
           return True
        d *= 2
    return False

def isPrime(n, primes, random, repetitions=10):
    """Primality test based on Miller-Rabin algorithm.

    It first checks wheter n is divisible by a small prime (using isDivisible).
    If not, it repeats the Rabin-Miller primality test (using millerRabin) for
    randomly chosen parameters a ∈ [2,n-2]. The number of repetitions is limited
    by the fourth argument. Function random(k) should return random numbers
    less than k.

    The result is the number of iterations of the Miller-Rabin algorithm until
    the test failed or -1 if n passed all tests.
    """
    if isDivisible(n, primes):
        return 0
    for i in range(repetitions):
        a = random(n-2) + 2
        # 2 <= a <= n-1
        if not millerRabin(a,n):
            return i+1
    return -1
