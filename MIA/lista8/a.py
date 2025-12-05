t = int(input())
for test in range(t):
    n = int(input())
    if n % 2 == 1:
        print(0)
    else:
        print((n // 4) + 1)
