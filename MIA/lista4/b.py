testy = int(input())

for test in range(testy):
    s = input()
    t = input()
    pos = len(t) // 2
    diff = len(t) // 2
    low = 0
    high = len(t) - 1

    s_end = 0
    while low <= high:
        mid = (low + high) // 2
        if s.find(t[:mid]) == -1:
            high = mid - 1
        elif mid < len(t) - 1 and s.find(t[: mid + 1]) > -1:
            low = mid + 1
        else:
            pos = mid
            break

    if pos == 0 and s.find(t) > -1:
        print("YES")
        continue

    if pos == len(t) - 1 and s.find(t) > -1:
        print("YES")
        continue

    s_start = s.find(t[:pos]) + pos - (len(t) - pos) - 1
    s_end = s.find(t[:pos]) + pos - 1
    if s.find(t[pos:][::-1], s_start, s_end) != -1:
        print("YES")
    else:
        print("NO")
    # print("pos", pos)
    # print("t0", t[:pos])
    # print("t1", t[pos:][::-1])
    # print("s_start", s[:s_start])
    # print("s_end", s[:s_end])
    # print("t", t[pos + 1 :][::-1])
