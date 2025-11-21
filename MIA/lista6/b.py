testy = int(input())

for test in range(testy):
    n = int(input())
    a = list(map(int, input().split()))
    partials = set()
    for el in a:
        if el not in partials:
            while el % 2 == 0:
                partials.add(el)
                el //= 2

    print(len(partials))
