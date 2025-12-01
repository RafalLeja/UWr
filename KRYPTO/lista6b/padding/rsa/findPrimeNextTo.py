"""Finds the smallest prime greater or equal to a given number.
"""

def findPrimeNextTo(n, testPrime):
    """Finds the smallest prime greater or equal to n.

    testPrime should return the number of iterations of the Miller-Rabin
    algorithm until the test failed or -1 if n passed all tests.
    """

    def printProgress(c):
        print(c, end='', flush=True)

    if n % 2 == 0:
        n += 1
    total = 0
    deep = 0
    deeper = 0
    tests = 0
    k = 0
    while True:
        k = testPrime(n)
        total += 1
        if k < 0:
            print('*')
            break
        if k > 0:
            tests += k
            deep += 1
            if k > 1:
                deeper += 1
                printProgress('*')
            else:
                printProgress('!')
        else:
            printProgress('.')
        n += 2

    return n, total, deep, deeper, tests
