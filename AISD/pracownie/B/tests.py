import random
from subprocess import Popen, PIPE, STDOUT
import math

def distance(x1, y1, x2, y2):
  return math.sqrt((x1 - x2)**2 + (y1 - y2)**2)

def triangle(res):
  circ = 0
  circ += distance(res[0][0], res[0][1], res[1][0], res[1][1])
  circ += distance(res[1][0], res[1][1], res[2][0], res[2][1])
  circ += distance(res[2][0], res[2][1], res[0][0], res[0][1])
  return circ

def main():
  n = int(input())
  visited = set()

  inputStr = str(n) + '\n'
  for i in range(n):
    x = random.randint(-(10**7), 10**7)
    y = random.randint(-(10**7), 10**7)
    if (x, y) in visited:
      i -= 1
      continue
    inputStr += str(x) 
    inputStr += ' ' 
    inputStr += str(y)
    inputStr += '\n'
    visited.add((x, y))

  trivComp = Popen(['gcc', 'triv.c', '-o', 'triv.o', '-lm'], stdout=PIPE, stderr=STDOUT)
  trivCall = Popen(['./triv.o'], stdout=PIPE, stdin=PIPE, stderr=STDOUT, text=True)
  trivRes = trivCall.communicate(input=inputStr)[0]
  trivRes = trivRes.split('\n')[0:3]
  for i in range(len(trivRes)):
    trivRes[i] = trivRes[i].split(' ')
    trivRes[i] = [int(trivRes[i][0]), int(trivRes[i][1])]

  optComp = Popen(['gcc', 'opt.c', '-o', 'opt.o', '-lm'], stdout=PIPE, stderr=STDOUT)
  optCall = Popen(['./opt.o'], stdout=PIPE, stdin=PIPE, stderr=STDOUT, text=True)
  optRes = optCall.communicate(input=inputStr)[0]
  optRes = optRes.split('\n')[0:3]
  for i in range(len(optRes)):
    optRes[i] = optRes[i].split(' ')
    optRes[i] = [int(optRes[i][0]), int(optRes[i][1])]

  if round(triangle(trivRes), 5) != round(triangle(optRes), 5):
    print('Test failed')
    print('Input:')
    print(inputStr)
    print('Trivial result:')
    print(trivRes)
    print('circumference:' + str(triangle(trivRes)))
    print('Optimal result:')
    print(optRes)
    print('circumference:' + str(triangle(optRes)))

if __name__ == '__main__':
  main()