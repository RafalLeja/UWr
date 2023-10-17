# Rafał Leja
# zadanie 2 lista 3 "labirynt"
# 17.10.2023

from collections import deque

labirynt = [
  ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
  ['X', ' ', ' ', ' ', 'X', ' ', ' ', ' ', 'X'],
  ['X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X'],
  ['X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X'],
  ['X', ' ', 'X', ' ', ' ', ' ', 'X', ' ', 'X'],
  ['X', ' ', 'X', 'X', 'X', 'X', 'X', ' ', 'X'],
  ['X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'],
  ['X', 'X', 'X', 'X', 'X', 'X', 'X', ' ', 'X']
]

def ucieczka(labirynt, start):
  
  if labirynt[start[0]][start[1]] == 'X':
    return "zły start"
  
  kolejka = deque([([start], start)])
  odwiedzone = set()
  
  while kolejka:
    trasa, aktualny = kolejka.popleft()
    
    # sprawdzanie czy jesteśmy na wyjściu
    if aktualny.count(0) > 0 or aktualny.count(len(labirynt)-1) > 0: 
      return trasa
    
    # sprawdzanie czy już byliśmy w tym miejscu
    if aktualny in odwiedzone:
      continue
    
    odwiedzone.add(aktualny)
    
    # dodawanie sąsiednich pól do kolejki
    for x,y in ((-1, 0), (0, -1), (0, 1), (1, 0)):
      if labirynt[aktualny[0]+x][aktualny[1]+y] == ' ':
        kolejka.append(
          (trasa + [(
            aktualny[0]+x,
            aktualny[1]+y)],
          (aktualny[0]+x, aktualny[1]+y)))
        
  return "brak wyjścia"

print(ucieczka(labirynt, (1,1)))

