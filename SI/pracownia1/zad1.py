import math
import sys

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
      for kX in [ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']:
        for kY in range(1, 9):
          # pozycja nie zmieniona
          if kX == self.wKing[0] and kY == int(self.wKing[1]):
            continue
          # ruch króla o więcej niż 1 pole
          if abs(ord(kX) - ord(self.wKing[0])) > 1 or abs(int(kY) - int(self.wKing[1])) > 1:
            continue
          # ruch króla na pole wieży
          if kX == self.wTower[0] and kY == int(self.wTower[1]):
            continue
          # ruch króla na pole bite przez czarnego króla
          if abs(ord(kX) - ord(self.bKing[0])) < 2 and abs(int(kY) - int(self.bKing[1])) < 2:
            continue
          self.neighbours.append(State("black", kX + str(kY), self.wTower, self.bKing, self.parents + [self]))
      for tX in [ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']:
        for tY in range(1, 9):
          # pozycja nie zmieniona
          if tX == self.wTower[0] and tY == int(self.wTower[1]): 
            continue
          # ruch wieży na ukos
          if tX != self.wTower[0] and tY != int(self.wTower[1]):
            continue
          # ruch wieży na pole białego króla
          if tX == self.wKing[0] and tY == int(self.wKing[1]):
            continue
          # ruch wieży na pole bite przez czarnego króla
          if abs(ord(tX) - ord(self.bKing[0])) < 2 and abs(int(tY) - int(self.bKing[1])) < 2:
            continue
          self.neighbours.append(State("black", self.wKing, tX + str(tY), self.bKing, self.parents + [self]))

    else:
      for kX in [ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']:
        for kY in range(1, 9):
          # pozycja się nie zmienia
          if kX == self.bKing[0] and kY == int(self.bKing[1]):
            continue
          # ruch króla o więcej niż 1 pole
          if abs(ord(kX) - ord(self.bKing[0])) > 1 or abs(kY - int(self.bKing[1])) > 1:
            continue
          # ruch króla na pole bite przez wieżę
          if kX == self.wTower[0] or kY == int(self.wTower[1]):
            continue
          # ruch króla na pole bite przez białego króla
          if abs(ord(kX) - ord(self.wKing[0])) < 2 and abs(kY - int(self.wKing[1])) < 2:
            continue
          # czy pozycja się powtarza?
          self.neighbours.append(State("white", self.wKing, self.wTower, kX + str(kY), self.parents + [self]))
    
  def __str__(self):
    return self.color + " " + self.wKing + " " + self.wTower + " " + self.bKing
  
  def checkMate(self):
    check = False
    if self.color == "black":
      # czy król jest bity przez króla?
      if abs(ord(self.wKing[0]) - ord(self.bKing[0])) < 2 and abs(int(self.wKing[1]) - int(self.bKing[1])) < 2:
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
      
  
  input_file = open("zad1_input.txt", "r")
  output_file = open("zad1_output.txt", "w")
  for line in input_file:
    line = line.split(" ")
    minMoves = solve(line[0], line[1], line[2], line[3], mode)
    output_file.write(str(minMoves) + "\n")
  return

def solve( color, wKing, wTower, bKing, mode):
  start = State(color, wKing, wTower, bKing)
  queue = [start]
  visited = []
  i = 0
  while len(queue) > 0:
    i += 1
    current = queue.pop(0)
    if str(current) in visited:
      continue
    current.generateNeighbours()

    queue += current.neighbours
    visited.append(str(current))
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