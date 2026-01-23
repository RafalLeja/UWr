import math

n = int(input())

arr = map(int, input().split())

sieve = [True] * (10**6 + 1)
sieve[0] = sieve[1] = False
for i in range(2, int((10**6) ** 0.5) + 1):
    if sieve[i]:
        for j in range(i * i, 10**6 + 1, i):
            sieve[j] = False

for a in arr:
    s = math.isqrt(a)
    y = False
    if s**2 == a and a != 1:
        prime = sieve[s]
        # if a % 2 == 0 and a != 2 and s != 2:
        #     prime = False
        # for x in range(3, s, 2):
        #     if a % x == 0:
        #         prime = False
        #         break

        y = prime
    print("YES" if y else "NO")
