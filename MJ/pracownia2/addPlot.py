import matplotlib.pyplot as plt
import os

DIR = './ADD/'

accuracy = {}
labelsX = []
labelsY = []

files = os.listdir(DIR)


def check(line):
    line = line.strip().split(' ')
    if len(line) == 4:
        return False

    a = int(line[0])
    b = int(line[2])
    op = line[1]
    res = line[4]
    if res.isdigit():
        res = int(res)
    else:
        return False

    if op == '+':
        return a + b == res
    elif op == '-':
        return a - b == res
    elif op == '*':
        return a * b == res
    elif op == '/':
        return a / b == res


for file in files:
    digits, num_eq = file.split('_')[1:]
    digits = int(digits)
    num_eq = int(num_eq.split('.')[0])
    if num_eq not in labelsY:
        labelsY.append(num_eq)
    hits = 0
    total = 0
    with open(DIR + file, 'r') as f:
        for line in f:
            total += 1
            if check(line):
                hits += 1
    if digits not in labelsX:
        labelsX.append(digits)
        accuracy[digits] = {}
    accuracy[digits][num_eq] = hits / total
    print(f'{file}: {hits}/{total}')

labelsX.sort()
labelsY.sort()

accMatrix = []
for x in labelsX:
    accMatrix.append([accuracy[x][y] for y in labelsY])

fig, ax = plt.subplots()
im = ax.imshow(accMatrix)
ax.set_title('dodawanie')

ax.set_xticks(range(len(labelsY)))
ax.set_xticklabels(labelsY)
ax.set_yticks(range(len(labelsX)))
ax.set_yticklabels(labelsX)

plt.xlabel('liczba równań')
plt.ylabel('liczba cyfr')


fig.colorbar(im, ax=ax, label='% trafień')

plt.show()
