
#         return 1
#     else:


tests = int(input())

for test in range(tests):
    s = input()
    t = input()

    if t == "a":
        print(1)
    elif 'a' in t:
        print(-1)
    else:
        print(2**len(s))
