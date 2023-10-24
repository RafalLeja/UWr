# Rafał Leja 340879
# zadanie 1 lista 4 "liczby pierwsze"
# 24.10.2023

import timeit
import math

setup = '''
import math

def prime(x):
  div = range(2, math.floor(math.sqrt(x))+1)
  for i in div:
    if x % i == 0:
      return False
  return True
'''


def pierwsze_imperatywna(n):
  out = []
  for x in range(2,n+1):
    prime = True
    for div in out:
      if x % div == 0:
        prime = False
    if prime:
      out.append(x)
  return out

def pierwsze_skladana(n):
  out = [x for x in range(2, n+1) if prime(x) ]
  return out
  
def prime(x):
  div = range(2, math.floor(math.sqrt(x))+1)
  for i in div:
    if x % i == 0:
      return False
  return True
  
def pierwsze_funkcyjna(n):
  out = list(filter(prime, range(2,n+1)))
  return out
  
p_i = '''
out = []
for x in range(2,n+1):
  prime = True
  for div in out:
    if x % div == 0:
      prime = False
  if prime:
    out.append(x)
'''

p_s = '''
out = [x for x in range(2, n+1) if prime(x) ]
'''
  
p_f = '''
out = list(filter(prime, range(2,n+1)))
'''
print(pierwsze_imperatywna(50))
print(pierwsze_skladana(50))
print(pierwsze_funkcyjna(50))

print("n p_i p_s p_f")
for x in range(5,15): 
  i = timeit.timeit(setup=f"{setup}\nn = {int(math.pow(2,x))}", stmt=p_i, number=10)
  s = timeit.timeit(setup=f"{setup}\nn = {int(math.pow(2,x))}", stmt=p_s, number=10)
  f = timeit.timeit(setup=f"{setup}\nn = {int(math.pow(2,x))}", stmt=p_f, number=10)
  print(f'{math.pow(2,x)} {i:.3} {s:.3} {f:.3}')
  