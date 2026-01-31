t = int(input())
for test in range(t):
    n = int(input())

    mines = []
    miners = []

    for i in range(2 * n):
        x, y = map(int, input().split())

        if x == 0:
            miners.append(y)
        else:
            mines.append(x)

    miners = sorted(miners, key=abs)
    mines = sorted(mines, key=abs)

    sum = 0.0
    for i in range(n):
        sum += ((miners[i] ** 2) + (mines[i] ** 2)) ** 0.5
    print(sum)
