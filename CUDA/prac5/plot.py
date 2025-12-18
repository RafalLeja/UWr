#!/bin/python3

import plotext as plt
import statistics

fastScores = {}
with open("./1_fast.txt", "r") as fastfile:
    for line in fastfile.readlines():
        nums = line.split(";")
        n = int(nums[0])
        mili = float(nums[1])
        if n not in fastScores:
            fastScores[n] = []
        fastScores[n].append(mili)


pedanticScores = {}
with open("./1_pedantic.txt", "r") as pedanticfile:
    for line in pedanticfile.readlines():
        nums = line.split(";")
        n = int(nums[0])
        mili = float(nums[1])
        if n not in pedanticScores:
            pedanticScores[n] = []
        pedanticScores[n].append(mili)

nDomain = list(fastScores.keys())
fastData = [statistics.median(fastScores[i]) for i in nDomain]
pedanticData = [statistics.median(pedanticScores[i]) for i in nDomain]
print(nDomain)
print(fastData)
# plt.doc.plot()
plt.plot(nDomain, fastData, label="fast")
plt.plot(nDomain, pedanticData, label="pedantic")
plt.xticks(nDomain, list(map(str, nDomain)))
# plt.xscale("log")
# plt.legend()
plt.show()
