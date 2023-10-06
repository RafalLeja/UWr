# Rafał Leja 340879
# zadanie 4 lista 1 "symulacja PI"
# 6.10.2023

import math
import random

ILOSC_RZUTOW = 10000
BOK=1 #rozmiar boku kwadratu

ltwo = 0
cltwt = 0


def w_kolku(x, y): #funkcja sprawdzająca czy punkt należy do koła
  odl = math.sqrt(x*x + y*y)
  return odl<=BOK

for rzut in range(ILOSC_RZUTOW):
  x = random.uniform(-BOK, BOK) #losowanie współrzędnych
  y = random.uniform(-BOK, BOK)
  
  print("rzut nr " + str(rzut+1))
  
  if w_kolku(x, y):
    print("trafiony!")
    ltwo +=1
  else:
    print("nietrafiony!")
    
  cltwt +=1
  print("pi = " + str(4.0*ltwo/cltwt) + "\n")
  
