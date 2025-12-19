testy = int(input())


def emotes(k, i):
    out = 0
    n = max(k, i)
    out += (n * (n + 1)) // 2
    if i > k:
        full = k * k
        oh = i - k
        # TODO:
        # obliczyć reszte piramidy potem bin search


for t in range(testy):
    k, x = map(int, input())
