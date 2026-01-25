import math

n = int(input())

arr = map(int, input().split())

arr = sorted(arr, reverse=True)
for a in arr:
    if a < 0:
        print(a)
        exit(0)
    s = math.isqrt(a)
    if s**2 != a:
        print(a)
        exit(0)
