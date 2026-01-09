import math

t = int(input())


for test in range(t):
    n = int(input())
    s = sum(map(int, list(str(n))))

    while math.gcd(n, s) == 1:
        # print(n)
        n += 1
        s = sum(map(int, list(str(n))))

    print(n)
