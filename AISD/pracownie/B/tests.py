import random
import subprocess 
import math
import time

def distance(x1, y1, x2, y2):

  return math.sqrt((x1 - x2)**2 + (y1 - y2)**2)

def triangle(res):
  circ = 0
  circ += distance(res[0][0], res[0][1], res[1][0], res[1][1])
  circ += distance(res[1][0], res[1][1], res[2][0], res[2][1])
  circ += distance(res[2][0], res[2][1], res[0][0], res[0][1])
  return circ

def main():
  inputFile = open('./test_set_1/ts1_input.txt', 'r').read()
  resFile = open('./test_set_1/ts1_output.txt', 'r').read()
  failedFile = open('failed.txt', 'w')
  visited = set()

  results = resFile.split('\n')[0:-1]
  for i in range(len(results)):
    results[i] = float(results[i].split(' ')[2])

  optComp = subprocess.run(['g++', 'reverse.cpp', '-o', 'reverse.exe'], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
  # optComp = subprocess.run(['gcc', 'trojkaty.c', '-o', 'trojkaty.exe'], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

  if optComp.returncode != 0:
    print('Compilation failed')
    print(optComp.stdout)
    return

  test = 0
  testLines = 0
  inputStr = ''
  numOfPoints = 0
  for (i, line) in enumerate(inputFile.split('\n')):
    if testLines == 0:
      if i != 0:
        # optRes = subprocess.run(['timeout 5'], text=True, capture_output=True, input=inputStr, timeout=60, shell=True)
        optRes = subprocess.run(['./reverse.exe'], text=True, capture_output=True, input=inputStr)
        # optRes = subprocess.run(['./trojkaty.exe'], text=True, capture_output=True, input=inputStr)

        timeout = 10
        while optRes.returncode != 0:
          if timeout == 0:
            print('Test failed timeout')
            print('Input: ')
            print(numOfPoints)
            print('Optimal result: ')
            print('Expected result: ')
            print(results[test])
            print('Test number: ' + str(test + 1))
            failedFile.write(inputStr)
            break
          timeout -= 1
          time.sleep(1)
        
        optRes = optRes.stdout
        optRes = optRes.split('\n')[0:3]

        for i in range(len(optRes)):
          optRes[i] = optRes[i].split(' ')
          optRes[i] = [int(optRes[i][0]), int(optRes[i][1])]
        
        if round(triangle(optRes), 5) != round(results[test], 5):
          print('Test failed')
          print('Input number:')
          # print(inputStr)
          print('Optimal result:')
          print(triangle(optRes))
          print(optRes)

          # print('circumference:' + str(triangle(optRes)))
          print('Expected result:')
          print(results[test])
          print('Test number: ' + str(test + 1))
        
        else:
          print('Test ' + str(test + 1) +  ' passed')
          print(optRes)

        test += 1

      testLines = int(line)
      numOfPoints = testLines
      inputStr = line + '\n'
      continue
    else:
      inputStr += line + '\n'
      testLines -= 1

if __name__ == '__main__':
  main()