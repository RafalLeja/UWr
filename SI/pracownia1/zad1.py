import math
import sys
from collections import deque

class State:
  def __init__(self, color, wKing, wTower, bKing, parent = None, depth = 0):
    self.color = color
    self.wKing = wKing
    self.wTower = wTower
    self.bKing = bKing
    self.parent = parent
    self.depth = depth

  def __str__(self):
    return f"{self.color} {chr(self.wKing[0]+96)}{self.wKing[1]} "\
          +f"{chr(self.wTower[0]+96)}{self.wTower[1]} "\
          +f"{chr(self.bKing[0]+96)}{self.bKing[1]}"
  
    
def generateNeighbours(state, visited):
  nextMoves = []
  
  if state.color == "white":
    for (x, y) in [(-1, -1), (0, -1),  (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1), (1, 1)]:
      kX = state.wKing[0] + x
      kY = state.wKing[1] + y
      # ruch króla poza planszę
      if kX < 1 or kX > 8 or kY < 1 or kY > 8:
        continue
      # ruch króla na pole wieży
      if kX == state.wTower[0] and kY == state.wTower[1]:
        continue
      # ruch króla na pole bite przez czarnego króla
      if abs(kX - state.bKing[0]) < 2 and abs(kY - state.bKing[1]) < 2:
        continue

      nm = State("black", (kX, kY), state.wTower, state.bKing, state, state.depth+1)
      pos = (nm.color, nm.wKing, nm.wTower, nm.bKing)
      if pos not in visited:
        nextMoves.append(nm)
        visited.add(pos)

    for tX in range(1, 9):
      # pozycja nie zmieniona
      if tX == state.wTower[0]: 
        continue   
      # ruch wieży na pole białego króla
      if tX == state.wKing[0] and state.wTower[1] == state.wKing[1]:
        continue
      # ruch wieży na pole bite przez czarnego króla
      if abs(tX - state.bKing[0]) < 2 and abs(state.wTower[1] - state.bKing[1]) < 2:
        continue
      nm = State("black", state.wKing, (tX, state.wTower[1]), state.bKing, state, state.depth+1)
      pos = (nm.color, nm.wKing, nm.wTower, nm.bKing)
      if pos not in visited:
        nextMoves.append(nm)
        visited.add(pos)

    for tY in range(1, 9):
      # pozycja nie zmieniona
      if tY == state.wTower[1]: 
        continue
      # ruch wieży na pole białego króla
      if tY == state.wKing[1] and state.wTower[0] == state.wKing[0]:
        continue
      # ruch wieży na pole bite przez czarnego króla
      if abs(tY - state.bKing[1]) < 2 and abs(state.wTower[0] - state.bKing[0]) < 2:
        continue

      nm = State("black", state.wKing, (state.wTower[0], tY), state.bKing, state, state.depth+1)
      pos = (nm.color, nm.wKing, nm.wTower, nm.bKing)
      if pos not in visited:
        nextMoves.append(nm)
        visited.add(pos)

  else:
    for (x, y) in [(-1, -1), (0, -1),  (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1), (1, 1)]:
      kX = state.bKing[0] + x
      kY = state.bKing[1] + y
      # ruch króla poza planszę
      if kX < 1 or kX > 8 or kY < 1 or kY > 8:
        continue
      # ruch króla na pole bite przez wieżę
      if kX == state.wTower[0] or kY == state.wTower[1]:
        continue
      # ruch króla na pole bite przez białego króla
      if abs(kX - state.wKing[0]) < 2 and abs(kY - state.wKing[1]) < 2:
        continue

      nm = State("white", state.wKing, state.wTower, (kX, kY), state, state.depth+1)
      pos = (nm.color, nm.wKing, nm.wTower, nm.bKing)
      if pos not in visited:
        nextMoves.append(nm)
        visited.add(pos)

  return nextMoves
  
def checkMate(state : State):
    # jedyne możliwe maty to gdy król jest na krawędzi planszy i jest atakowany przez wieżę
    if state.bKing[0] == 1 and state.wKing[0] == 3 and state.bKing[1] == state.wKing[1] and state.wTower[0] == 1 and abs(state.bKing[1] - state.wTower[1]) > 1:
        return True

    if state.bKing[0] == 8 and state.wKing[0] == 6 and state.bKing[1] == state.wKing[1] and state.wTower[0] == 8 and abs(state.bKing[1] - state.wTower[1]) > 1:
        return True

    if state.bKing[1] == 1 and state.wKing[1] == 3 and state.bKing[0] == state.wKing[0] and state.wTower[1] == 1 and abs(state.bKing[0] - state.wTower[0]) > 1:
        return True

    if state.bKing[1] == 8 and state.wKing[1] == 6 and state.bKing[0] == state.wKing[0] and state.wTower[1] == 8 and abs(state.bKing[0] - state.wTower[0]) > 1:
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
  start = State(color, (ord(wKing[0])-96, int(wKing[1])), 
                       (ord(wTower[0])-96, int(wTower[1])), 
                       (ord(bKing[0])-96, int(bKing[1])))
  queue = deque([start])
  visited = set([])
  total = 0
  while len(queue) > 0:
    total += 1
    current = queue.popleft()

    if checkMate(current):
      moves = 0
      if mode == "debug": 
        print("Checkmate")
      
      while current.parent != None:
        if mode == "debug":
          print(str(current))
        current = current.parent
        moves += 1

      return moves
    
    queue.extend(generateNeighbours(current, visited))


  return math.inf

if __name__ == "__main__":
  main()