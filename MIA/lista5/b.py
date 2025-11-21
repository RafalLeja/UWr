from collections import deque

tests = int(input())

for test in range(tests):
    n = int(input())
    s = input()
    stack = deque()
    depths = {i: 0 for i in range(n + 2)}
    sum = 0
    for i, c in enumerate(s):
        if c == "(":
            depths[len(stack)] = 1
            stack.append(i)
        else:
            prev = stack.pop()
            sum += depths[len(stack) + 1]
            depths[len(stack) + 1] = 0

    sum += depths[0]
    print(sum)
