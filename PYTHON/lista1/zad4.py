import math
import random

ilosc_rzutow = 30

BOK=1 #rozmiar boku kwadratu
ltwo = 0
cltwt = 0


def w_kolku(x, y):
  odl = math.sqrt(x*x + y*y)
  return odl<=BOK

for rzut in range(ilosc_rzutow):
  x = random.randrange(-BOK, BOK);
  y = random.randrange(-BOK, BOK);
  if w_kolku(x, y):
    ltwo +=1
  cltwt +=1
  print("rzut nr " + str(rzut))
  
