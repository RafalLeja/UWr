testy = int(input())

for test in range(testy):
    s = input()
    t = input()
    yes = False

    for start in range(len(s)):
        for right in range(1, len(t) + 1):
            if start + right > len(s):
                break

            if s[start : start + right] != t[:right]:
                continue

            rem = t[right:]
            ok = True
            for j in range(len(rem)):
                pos = start + right - 2 - j
                if pos < 0 or s[pos] != rem[j]:
                    ok = False
                    break

            if ok:
                yes = True
                break
        if yes:
            break
    if yes:
        print("YES")

    else:
        print("NO")

    # print("t", t[pos + 1 :][::-1])
