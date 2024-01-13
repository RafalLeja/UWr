def Newton(fn, n, a, b):
    tn = [a + (b - a) * i / n for i in range(n + 1)]

    a = []
    for i in range(n + 1):
        a.append(fn(tn[i]))