# Rafał Leja 340879
# MIA 2025
# Zadanie B, Lista 1
# 07.10.2025

testy = int(input())
for test in range(testy):
    num = int(input())
    arr = list(map(int, input().split(" ")))

    dp = [0 for i in range( num)]
    start = [[] for i in range(num + 1)]
    ilosc = [0 for i in range(num + 1)]

    if arr[0] == 1:
        dp[0] = 1
    ilosc[arr[0]] = 1
    start[arr[0]].append(0)

    for i in range(1, num):
        start[arr[i]].append(i)
        ilosc[arr[i]] += 1
        start[arr[i]] = start[arr[i]][-arr[i]:]

        bierz = 0
        if ilosc[arr[i]] >= arr[i]:
            poprzednie = dp[start[arr[i]].pop(-arr[i]) -1] if start[arr[i]][0] > 0 else 0
            bierz = arr[i] + poprzednie

        zostaw = dp[i-1]

        dp[i] = max(bierz, zostaw)


    print(dp[-1])




