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
      for tX in [ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']:
        for tY in range(1, 9):
          for kX in [ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']:
            for kY in range(1, 9):
              # pozycja nie zmieniona
              if tX == self.wTower[0] and tY == self.wTower[1] and kX == self.wKing[0] and kY == self.wKing[1]: 
                continue
              # ruch wieży na ukos
              if tX != self.wTower[0] and tY != self.wTower[1]:
                continue
              # ruch króla o więcej niż 1 pole
              if abs(ord(kX) - ord(self.wKing[0])) > 1 or abs(kY - self.wKing[1]) > 1:
                continue
              self.neighbours.append(State("black", tX + tY, kX + kY))

    else:
      for kX in [ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']:
        for kY in range(1, 9):
          if kX == self.bKing[0] and kY == self.bKing[1]:
            continue
          if abs(ord(kX) - ord(self.bKing[0])) > 1 or abs(kY - self.bKing[1]) > 1:
            continue
          self.neighbours.append(State("white", self.wKing, self.wTower, kX + kY))
    
  def __str__(self):
    return self.color + " " + self.wKing + " " + self.wTower + " " + self.bKing
  
  def checkMate(self):
    if self.color == "white":
      if self.wKing[0] == self.bKing[0] or self.wKing[1] == self.bKing[1]:
        return True
      if abs(ord(self.wKing[0]) - ord(self.bKing[0])) == abs(int(self.wKing[1]) - int(self.bKing[1])):
        return True
      if self.wKing[0] == self.wTower[0] or self.wKing[1] == self.wTower[1]:
        return True
      return False
    else:
      return False

def main():
  arguments = sys.argv[1:]
  mode = "normal"

  if arguments[0] == "--debug":
    mode = "debug"
  
  input_file = open("zad1_input.txt", "r")
  output_file = open("zad1_output.txt", "w")
  for line in input_file:
    line = line.split(" ")
    minMoves = solve(line[0], line[1], line[2], line[3], mode)

def solve( color, wKing, wTower, bKing, mode):
  

  return 



if __name__ == "__main__":
  main()