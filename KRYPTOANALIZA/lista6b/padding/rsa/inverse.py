"""Computes x⁻¹ mod y.

Obsolete since Python 3.8, since pow now does the trick.
"""

def inv(x, y):
    """Computes x⁻¹ mod y. With Python 3.8 or newer use pow(x, -1, y) instead.

    If x is not invertible modulo y, raises ValueError('not invertible').
    """
    t = 0
    r = y
    t1 = 1
    r1 = x
    while r1 != 0:
        q = r // r1
        (t, t1) = (t1, t - q * t1)
        (r, r1) = (r1, r - q * r1)
    if r > 1:
        raise ValueError('not invertible')
    if t < 0:
        t += y
    return t
