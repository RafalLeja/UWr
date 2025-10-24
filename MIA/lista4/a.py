testy = int(input())

for test in range(testy):
    n = int(input())
    s = input()
    sum = 0
    bit = 1
    idx = 0
    while s.find(str(bit), idx) != -1:
        idx = s.find(str(bit), idx) + 1
        sum += 1
        bit = 1 - bit
    print(sum)
