import re

tests = int(input())

for test in range(tests):
    s = input()
    # if re.match(r"^E+N$", s):
    if s.count("N") == 1:
        print("NO")
    else:
        print("YES")
