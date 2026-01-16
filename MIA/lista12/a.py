t = int(input())

for test in range(t):
    n, m = map(int, input().split())
    x1, y1, x2, y2 = map(int, input().split())

    if ((x1 == 1 or x1 == n) and (y1 == 1 or y1 == m)) or (
        (x2 == 1 or x2 == n) and (y2 == 1 or y2 == m)
    ):
        print(2)
        continue
    elif (x1 == 1 or x1 == n or y1 == 1 or y1 == m) or (
        x2 == 1 or x2 == n or y2 == 1 or y2 == m
    ):
        print(3)
        continue

    print(4)
