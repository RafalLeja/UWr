import re
import sys

n = int(input())

level = input()

if level.count("*") < 5:
    print("no")
    sys.exit()

reg = r"\*"
for i in range(0, n):
    fullReg = r".*" + reg * 4 + r"\*.*"
    if re.search(fullReg, level) is not None:
        print("yes")
        sys.exit()

    reg += r"."

print("no")
