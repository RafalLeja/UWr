testy = int(input())

for test in range(testy):
    l, r = list(map(int, input().split()))
    # print(f"l: {l}, r: {r}")
    if r % 2 == 0 and (r // 2) >= l:
        print(f"{r // 2} {r}")
    elif r % 2 == 1 and ((r - 1) // 2) >= l:
        print(f"{(r - 1) // 2} {r - 1}")
    else:
        print("-1 -1")
