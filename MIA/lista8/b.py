t = int(input())
for test in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    if arr[-1] == -1 and arr[0] == -1:
        arr[0] = 0
        arr[-1] = 0
    if arr[0] == -1:
        arr[0] = arr[n - 1]
    if arr[-1] == -1:
        arr[-1] = arr[0]
    for i in range(len(arr) - 2):
        if arr[i + 1] == -1:
            arr[i + 1] = 0
    print(abs(arr[0] - arr[-1]))
    print(" ".join(map(str, arr)))
