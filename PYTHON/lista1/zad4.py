import math
import random

ilosc_rzutow = 300

BOK=1 #rozmiar boku kwadratu
ltwo = 0
cltwt = 0


def w_kolku(x, y):
  odl = math.sqrt(x*x + y*y)
  return odl<=BOK

for rzut in range(ilosc_rzutow):
  x = random.uniform(-BOK, BOK);
  y = random.uniform(-BOK, BOK);
  print("rzut nr " + str(rzut+1))
  if w_kolku(x, y):
    print("trafiony!")
    ltwo +=1
  else:
    print("nietrafiony!")
  cltwt +=1
  print("pi = " + str(4*ltwo/cltwt) + "\n")
  
