import random

moves = {'U' : (0, -1), 'D' : (0, 1), 'L' : (-1, 0), 'R' : (1, 0)}
output_file = open('zad_output.txt', 'w')
walls = set()
goals = set()
visitedMin = set()
visited = set()

class State:
  def __init__(self, commandos, prevMoves = ''):
    self.prevMoves = prevMoves
    self.commandos = set(commandos)
    if self.commandos <= goals:
      output_file.write(prevMoves)
      exit(0)
    self.commandos = tuple(sorted(self.commandos))
    return

  def __lt__(self, other):
    return len(self.prevMoves) < len(other.prevMoves)

  # def check(self):
  #   for i in range(len(self.commandos)):
  #     if self.commandos[i] not in goals:
  #       return False
  #   return True

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

class minimizingState:
  def __init__(self, commandos, prevMoves = ''):
    self.prevMoves = prevMoves
    self.commandos = set(commandos)
    # if len(self.commandos) <= 3:
    #   output_file.write(prevMoves)
    #   exit(0)
    self.commandos = tuple(sorted(self.commandos))
    return

  def __lt__(self, other):
    return len(self.commandos) < len(other.commandos)

  # def check(self):
  #   for i in range(len(self.commandos)):
  #     if self.commandos[i] not in goals:
  #       return False
  #   return True

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
  usedMoves = 0
  minimizingMoves = ''
  
  lines = input_file.readlines()
  x = len(lines[0])-1
  y = len(lines)
  board = []
  for line in lines:
    board.append(list(line.strip()))
  
  if MAX_MOVES - 2*x - 2*y > x + y:
    usedMoves = x*2 + y*2
    for i in range(x):
      makeMove(board, 'R', output_file)
    for i in range(y):
      makeMove(board, 'D', output_file)
    for i in range(x):
      makeMove(board, 'L', output_file)
    for i in range(y):
      makeMove(board, 'U', output_file)
  # commandos = findCommandos(board)
  # prevCommandos = len(commandos)
  # for i in range(80):
    # randomMove = random.choice(list(moves.keys()))
    # makeMove(board, randomMove, output_file)


  # printBoard(board)

  findWalls(board)
  findGoals(board)
  commandos = findCommandos(board)

  # minDeque = [minimizingState(commandos)]
  # while len(minDeque) > 0:
  #   state = minDeque.pop(0)

  #   if state.commandos in visitedMin:
  #     continue
  #   visitedMin.add(state.commandos)

  #   if len(commandos) <= 3:
  #     minimizingMoves += state.prevMoves
  #     usedMoves += len(state.prevMoves)
  #     break

  #   if len(state.prevMoves) > 5:
  #     # output_file.write(state.prevMoves)
  #     minimizingMoves += state.prevMoves
  #     usedMoves += len(state.prevMoves)
  #     break

  #   for nextState in state.nextStates():
  #     minDeque.append(nextState)
  #   minDeque.sort()

  # # printBoard(board)
  # print(minimizingMoves)

  commandos = findCommandos(board)
  # print(commandos)

  deque = [State(commandos, minimizingMoves)]

  while len(deque) > 0:
    print(len(deque))
    state = deque.pop(0)

    if state.commandos in visited:
      continue
    visited.add(state.commandos)

    if len(state.prevMoves) > MAX_MOVES-usedMoves:
      continue
    for nextState in state.nextStates():
      deque.append(nextState)
    deque.sort()


  input_file.close()
  # output_file.write(moveHistory)
  output_file.close()

if __name__ == "__main__":
  main()