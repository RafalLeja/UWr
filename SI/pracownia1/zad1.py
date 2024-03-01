import math
import sys
from collections import deque

class State:
  def __init__(self, color, wKing, wTower, bKing, parents = []):
    self.color = color
    self.wKing = wKing
    self.wTower = wTower
    self.bKing = bKing
    self.parents = parents
    self.neighbours = []

  def generateNeighbours(self):
    if self.color == "white":
      for x in [-1, 0, 1]:
        for y in [-1, 0, 1]:
          kX = self.wKing[0] + x
          kY = self.wKing[1] + y
          # pozycja nie zmieniona
          if kX == self.wKing[0] and kY == self.wKing[1]:
            continue
          # ruch króla poza planszę
          if kX < 1 or kX > 8 or kY < 1 or kY > 8:
            continue
          # ruch króla na pole wieży
          if kX == self.wTower[0] and kY == self.wTower[1]:
            continue
          # ruch króla na pole bite przez czarnego króla
          if abs(kX - self.bKing[0]) < 2 and abs(kY - self.bKing[1]) < 2:
            continue

          self.neighbours.append(State("black", [kX, kY], self.wTower, self.bKing, self.parents + [self]))

      for tX in range(1, 9):
        # pozycja nie zmieniona
        if tX == self.wTower[0]: 
          continue   
        # ruch wieży na pole białego króla
        if tX == self.wKing[0] and self.wTower[1] == self.wKing[1]:
          continue
        # ruch wieży na pole bite przez czarnego króla
        if abs(tX - self.bKing[0]) < 2 and abs(self.wTower[1] - self.bKing[1]) < 2:
          continue
        self.neighbours.append(State("black", self.wKing, [tX, self.wTower[1]], self.bKing, self.parents + [self]))

      for tY in range(1, 9):
        # pozycja nie zmieniona
        if tY == self.wTower[1]: 
          continue
        # ruch wieży na pole białego króla
        if tY == self.wKing[1] and self.wTower[0] == self.wKing[0]:
          continue
        # ruch wieży na pole bite przez czarnego króla
        if abs(tY - self.bKing[1]) < 2 and abs(self.wTower[0] - self.bKing[0]) < 2:
          continue

        self.neighbours.append(State("black", self.wKing, [self.wTower[0], tY], self.bKing, self.parents + [self]))

    else:
      for x in [-1, 0, 1]:
        for y in [-1, 0, 1]:
          kX = self.bKing[0] + x
          kY = self.bKing[1] + y
          # pozycja się nie zmienia
          if kX == self.bKing[0] and kY == self.bKing[1]:
            continue
          # ruch króla poza planszę
          if kX < 1 or kX > 8 or kY < 1 or kY > 8:
            continue
          # ruch króla na pole bite przez wieżę
          if kX == self.wTower[0] or kY == self.wTower[1]:
            continue
          # ruch króla na pole bite przez białego króla
          if abs(kX - self.wKing[0]) < 2 and abs(kY - self.wKing[1]) < 2:
            continue

          self.neighbours.append(State("white", self.wKing, self.wTower, [kX, kY], self.parents + [self]))
    
  def __str__(self):
    return f"{self.color} {chr(self.wKing[0]+96)}{self.wKing[1]} "\
          +f"{chr(self.wTower[0]+96)}{self.wTower[1]} "\
          +f"{chr(self.bKing[0]+96)}{self.bKing[1]}"
  
  def __hash__(self) -> int:
    return hash(str(self))
    
  def checkMate(self):
    if self.color == "black":
      check = False
      # czy król jest bity przez króla?
      if abs(self.wKing[0] - self.bKing[0]) < 2 and abs(self.wKing[1] - self.bKing[1]) < 2:
        check = True
      # czy król jest bity przez wieżę?
      if self.bKing[0] == self.wTower[0] or self.bKing[1] == self.wTower[1]:
        check = True
      if check == True and len(self.neighbours) == 0:
        return True
    return False

def main():
  arguments = sys.argv[1:]
  mode = "normal"

  if len(arguments) > 0:
    if arguments[0] == "--debug":
      mode = "debug"
      
  input_file = open('zad1_input.txt', "r")
  output_file = open('zad1_output.txt', "w")
  for line in input_file:
    line = line.split(" ")
    minMoves = solve(line[0], line[1], line[2], line[3], mode)
    print(minMoves)
    output_file.write(str(minMoves) + "\n")
  return

def solve( color, wKing, wTower, bKing, mode):
  start = State(color, [ord(wKing[0])-96, int(wKing[1])], 
                       [ord(wTower[0])-96, int(wTower[1])], 
                       [ord(bKing[0])-96, int(bKing[1])])
  queue = deque([start])
  visited = set([])
  while len(queue) > 0:
    current = queue.popleft()

    if current in visited:
      continue
    visited.add(current)
    
    current.generateNeighbours()
    queue.extend(current.neighbours)

    if current.checkMate():
      if mode == "debug": 
        print("Checkmate")
        for p in current.parents:
          print(str(p))
        print(str(current))
      return len(current.parents)

  return math.inf

if __name__ == "__main__":
  main()