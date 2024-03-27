import math

moves = {'U' : (0, -1), 'D' : (0, 1), 'L' : (-1, 0), 'R' : (1, 0)}
output_file = open('zad_output.txt', 'w')
walls = set()
goals = set()
visited = set()

class State:
  def __init__(self, commandos, prevMoves = ''):
    self.commandos = tuple(sorted(set(commandos)))
    self.prevMoves = prevMoves
    self.heuristic = self.f()
    if self.check():
      output_file.write(prevMoves)
      exit(0)

    return

  def h(self):
    dists = []
    for commando in self.commandos:
      for goal in goals:
        dists.append(abs(commando[0] - goal[0]) + abs(commando[1] - goal[1]))
        # dists.append(math.sqrt(abs(commando[0] - goal[0])**2 + (commando[1] - goal[1])**2))
    return max(dists)

  def g(self):
    return len(self.prevMoves)

  def f(self):
    W = 1000
    return self.g() + self.h() * W

  def __lt__(self, other):
    # return len(self.prevMoves) < len(other.prevMoves)
    if self.heuristic == other.heuristic:
      return len(self.commandos) < len(other.commandos)
    return self.heuristic < other.heuristic

  def check(self):
    for i in range(len(self.commandos)):
      if self.commandos[i] not in goals:
        return False
    return True

  def tryMove(self, direction):
    newCommandos = ()
    for commando in self.commandos:
      newCommando = (commando[0] + moves[direction][0], commando[1] + moves[direction][1])
      if newCommando in walls:
        newCommandos += (commando,)
      else:
        newCommandos += (newCommando,)
    return newCommandos

  def nextStates(self):
    states = []
    for direction in moves.keys():
      newCommandos = self.tryMove(direction)
      if newCommandos != self.commandos:
        # print(self.prevMoves + direction)
        states.append(State(newCommandos, self.prevMoves + direction))
    return states

def move(board, direction):
  vRange = range(len(board))
  hRange = range(len(board[0]))
  if direction == 'D':
    vRange = range(len(board)-1, -1, -1)
  if direction == 'R':
    hRange = range(len(board[0])-1, -1, -1)
  for y in vRange:
    for x in hRange:
      if board[y][x] == 'B':
        newX = x + moves[direction][0]
        newY = y + moves[direction][1]

        if newY < 0 or newY >= len(board) or newX < 0 or newX >= len(board[0]):
          continue
        if board[newY][newX] == '#':
          continue
        if board[newY][newX] == ' ':
          board[y][x] = 'G'
          board[newY][newX] = 'S'
        if board[newY][newX] == 'S':
          board[y][x] = 'G'
          board[newY][newX] = 'S'
        else:
          board[y][x] = 'G'
      elif board[y][x] == 'S':
        newX = x + moves[direction][0]
        newY = y + moves[direction][1]

        # print(board[y][x])
        # print(board[newY][newX])
        if newY < 0 or newY >= len(board) or newX < 0 or newX >= len(board[0]):
          continue
        if board[newY][newX] == '#':
          continue
        if board[newY][newX] == ' ':
          board[y][x] = ' '
          board[newY][newX] = 'S'
        if board[newY][newX] == 'G':
          board[y][x] = ' '
          board[newY][newX] = 'B'
        else:
          board[y][x] = ' '

def makeMove(board, direction, output_file):
  output_file.write(direction)
  move(board, direction)
  if checkWin(board):
    exit(0)
  return

def checkWin(board):
  for row in board:
    if 'S' in row:
      return False
  return True

def printBoard(board):
  print("---------------")
  for row in board:
    print(row)
  return

def findWalls(board):
  for y in range(len(board)):
    for x in range(len(board[0])):
      if board[y][x] == '#':
        walls.add((x, y))

def findCommandos(board):
  commandos = ()
  for y in range(len(board)):
    for x in range(len(board[0])):
      if board[y][x] == 'S' or board[y][x] == 'B':
        commandos += ((x, y),)
  return commandos

def findGoals(board):
  for y in range(len(board)):
    for x in range(len(board[0])):
      if board[y][x] == 'G' or board[y][x] == 'B':
        goals.add((x, y))

def main():
  input_file = open('zad_input.txt', 'r')
  MAX_MOVES = 150
  
  lines = input_file.readlines()
  x = len(lines[0])-1
  y = len(lines)
  board = []
  for line in lines:
    board.append(list(line.strip()))

  # printBoard(board)

  findWalls(board)
  findGoals(board)
  commandos = findCommandos(board)

  deque = [State(commandos)]
  while len(deque) > 0:
    state = deque.pop(0)

    if state.commandos in visited:
      continue
    visited.add(state.commandos)

    if len(state.prevMoves) > MAX_MOVES:
      continue
    for nextState in state.nextStates():
      deque.append(nextState)
    deque.sort()


  input_file.close()
  # output_file.write(moveHistory)
  output_file.close()

if __name__ == "__main__":
  main()