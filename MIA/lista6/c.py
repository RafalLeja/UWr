n = int(input())


def divisors(x):
    divs = set()
    j = 2
    while j * j <= x:
        if x % j == 0:
            divs.add(j)
            while x % j == 0:
                x //= j
        j += 1
    if x > 1:
        divs.add(x)
    return divs


partials = set()
a, b = map(int, input().split())
partials.update(divisors(a))
partials.update(divisors(b))

# print(partials)
for i in range(n - 1):
    a, b = map(int, input().split())
    good = False

    to_remove = set()

    for div in sorted(list(partials)):
        if a % div == 0 or b % div == 0:
            good = True
            break
        if a % div != 0 and b % div != 0:
            to_remove.add(div)

    partials -= to_remove
    if good:
        continue
    else:
        print("-1")
        exit(0)

print(sorted(list(partials))[0])
