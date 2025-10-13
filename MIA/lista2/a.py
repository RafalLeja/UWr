# Rafał Leja
# MIA lista 2 zadanie A
testy = int(input())
for test in range(testy):
    n = int(input())

    f_min = list()
    s_min = list()
    for tab in range(n):
        dlogosc = input()
        arr = input()
        arr = list(map(int, arr.split(' ')))
        arr.sort()

        f_min.append(arr[0])
        s_min.append(arr[1])


    print(sum(s_min) - min(s_min) + min(f_min))
        


