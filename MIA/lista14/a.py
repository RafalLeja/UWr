n = int(input())

sum_up = 0
sum_down = 0
for i in range(n):
    x, y = map(int, input().split())
    if x > 0:
        sum_up += 1
    else:
        sum_down += 1

# print(sum_up, sum_down)
if n <= 2:
    print("YES")
elif sum_up <= 1 or sum_down <= 1:
    print("YES")
else:
    print("NO")
