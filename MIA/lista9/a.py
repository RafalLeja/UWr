n, m = list(map(int, input().split()))
laces_per_student = [0 for _ in range(n)]
students_per_student = [[] for _ in range(n)]
for lace in range(m):
    a, b = list(map(int, input().split()))
    laces_per_student[a - 1] += 1
    students_per_student[a - 1].append(b)
    laces_per_student[b - 1] += 1
    students_per_student[b - 1].append(a)

steps = 0
while laces_per_student.count(1) > 0:
    to_kick = []
    start = 0
    idx = laces_per_student.index(1, start)
    while idx != -1:
        to_kick.append(idx)
        start = idx + 1
        try:
            idx = laces_per_student.index(1, start)
        except ValueError:
            idx = -1

    for student in to_kick:
        laces_per_student[student] = 0
        for friend in students_per_student[student]:
            laces_per_student[friend - 1] -= 1
    steps += 1

print(steps)
