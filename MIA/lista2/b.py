# Rafał Leja
# MIA lista 2 zadanie b
testy = int(input())

for test in range(testy):
    n, k = list(map(int, input().split()))

    a = list(map(int, input().split()))
    suma = 0
    i = 0
    while(k > 0):

        if i < len(a)-1:

            ilosc = min(k, (10**a[i+1] // 10**a[i]) -1)
            if ilosc == k:
                ilosc += 1
            k -= ilosc
            suma += ilosc * (10**a[i])
        else:
            suma += (k + 1) * 10 **a[i]
            k = 0
        i +=1

    print(suma)
