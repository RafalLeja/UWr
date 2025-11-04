from fractions import Fraction

n = 1966981193543797
e = 323815174542919

en = Fraction(e, n)
print(en)
pq = en.limit_denominator(max_denominator=e - 1)
p, q = en.as_integer_ratio()
while p * q != n:
    pq = pq.limit_denominator(max_denominator=q - 1)

    print(pq)
    p, q = pq.as_integer_ratio()
print(pq)
