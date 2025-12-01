import math

tests = int(input())
for test in range(tests):
    n, h = list(map(int, input().split(" ")))
    arr = list(map(int, input().split(" ")))

    # starting_k = 1
    starting_k = math.ceil(h / n)
    # if starting_k * n >= h:
    #     print(starting_k)
    #     continue

    start = starting_k
    end = h + 1

    diffs = [arr[i + 1] - arr[i] for i in range(len(arr) - 1)]
    while start < end:
        k = (end + start) // 2
        damage = k
        for i in range(len(arr) - 1):
            damage += (k * (k <= diffs[i])) + (diffs[i] * (diffs[i] < k))

        if damage >= h:
            end = k
        else:
            start = k + 1

    print(start)
