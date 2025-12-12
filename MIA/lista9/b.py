n = int(input())
arr = [-1] + list(map(int, input().split()))

minimum = 0


def fix(idx):
    global minimum
    global arr
    if idx > (2 ** (n + 1)) - 1:
        # lisc
        return 0

    sum_left = fix(2 * idx)
    sum_right = fix((2 * idx) + 1)
    diff = abs(sum_left - sum_right)
    minimum += diff
    # print(
    # f"idx: {idx}, sum_left: {sum_left}, sum_right: {sum_right}, diff: {diff}, minimum: {minimum}"
    # )
    return max(sum_left, sum_right) + arr[idx - 1]


fix(1)
print(minimum)
