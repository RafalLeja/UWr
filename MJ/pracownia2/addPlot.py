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

fig, ax = plt.subplots(2)
im = ax[0].imshow(accMatrix)
ax[0].set_title('dodawanie')

ax[0].set_xticks(range(len(labelsY)))
ax[0].set_xticklabels(labelsY)
ax[0].set_yticks(range(len(labelsX)))
ax[0].set_yticklabels(labelsX)

ax[0].set_xlabel('liczba równań')
ax[0].set_ylabel('liczba cyfr')


fig.colorbar(im, ax=ax[0], label='% trafień')

for i in range(len(accMatrix)):
    ax[1].plot(accMatrix[i], label=str(i+1))
# plt.plot(accMatrix)

# ax[1].xticks(range(len(labelsY)), labelsY)
# ax[1].yticks(range(len(labelsX)), labelsX)

ax[1].set_xlabel('liczba równań')
ax[1].set_ylabel('celność')


# fig.colorbar(im, ax=ax, label='% trafień')
ax[1].legend()

# plt.show()

plt.show()
