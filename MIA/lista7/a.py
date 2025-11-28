n = int(input())
t_n = list(map(int, input().split(" ")))

# sushi = {1: 2, 2: 1}
prev_type = t_n[0]
counts = []
length = 1
for t in t_n[1:]:
    if t == prev_type:
        length += 1
    if t != prev_type:
        # print(t)
        counts.append(length)
        prev_type = t
        length = 1
counts.append(length)

max_len = 0
for i in range(len(counts) - 1):
    length = min(counts[i], counts[i + 1])
    if length > max_len:
        max_len = length

# print(counts)
print(2 * max_len)
