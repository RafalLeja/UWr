from fractions import Fraction
from math import isqrt

n = int(input("Podaj n:\n").strip())
e = int(input("Podaj e:\n").strip())
c = int(input("Podaj c:\n").strip())


def check_c(e, n, p, q, c):
    a = 1
    b = -(n - c + 1)
    delta = (b**2) - (4 * a * n)
    x1 = (-b + isqrt(delta)) / (2 * a)
    x2 = (-b - isqrt(delta)) / (2 * a)
    return x1, x2


def unravel_en(e, n):
    frac = Fraction(e, n)
    en = frac

    p2, p1 = 0, 1
    q2, q1 = 1, 0
    c = 0
    while frac.numerator != 0:
        a = frac.__floor__()
        if frac - a == 0:
            break
        frac = 1 / (frac - a)
        p = a * p1 + p2
        q = a * q1 + q2

        if p > 0 and frac - en > 0 and q % 2 == 1:
            c = Fraction((e * q) - 1, p)
            if c.denominator == 1:
                x1, x2 = check_c(e, n, p, q, c.numerator)
                if x1.is_integer() and x2.is_integer() and x1 * x2 == n:
                    return int(x1), int(x2)

        p2, p1 = p1, p
        q2, q1 = q1, q
    return 0, 0


p, q = unravel_en(e, n)
if p > 0:
    print("Solution found:")
    print(f"p = {p}")
    print(f"q = {q}")
    phi = (p - 1) * (q - 1)
    print(f"phi = {phi}")
    d = pow(e, -1, phi)
    print(f"d = {d}")

    m = pow(c, d, n)
    print(f"m = {m}")
else:
    print("No solution found")
