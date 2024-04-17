import random
from itertools import combinations

DEBUG = False
DONE_ROWS = set()
DONE_COLS = set()
  
def singleDist(board, row):
  min = len(board)
  numOfSquares = sum(row)
  for i in range(len(board)):
    if board[i] == '#':
      numOfSquares -= 1
  return numOfSquares

def markRow(board, rowIDx):
  if rowIDx in DONE_ROWS:
    return
  DONE_ROWS.add(rowIDx)
  for i in range(len(board[0])):
    if board[rowIDx][i] == ' ':
      board[rowIDx][i] = '.'
  return

def markCol(board, colIDx):
  if colIDx in DONE_COLS:
    return
  DONE_COLS.add(colIDx)
  for i in range(len(board)):
    if board[i][colIDx] == ' ':
      board[i][colIDx] = '.'
  return

def permutate(board, row):
  options = []
  n = len(board) - sum(row) - len(row) + 1
  block_idx = list(combinations(range(n+len(row)), len(row)))
  for idx in block_idx:
    options.append(generateRow(row, idx, n)[:-1])
  return options

def generateRow(row, block_idx, n):
  out = []
  for i in range(len(row)+n):
    if i in block_idx:
      b = block_idx.index(i)
      out.extend(['#']*row[b])
      out.append('.')
    else:
      out.append('.')
  return out

def failedRows(board, rows):
  fRows = []
  for r in range(len(rows)):
    if singleDist(board[r], rows[r]) != 0:
      fRows.append(r)
    elif singleDist(board[r], rows[r]) < 0:
      return None
    else:
      markRow(board, r)
  return fRows

def failedCols(board, cols):
  fCols = []
  for c in range(len(cols)):
    col = []
    for r in range(len(board)):
      col.append(board[r][c])
    if singleDist(col, cols[c]) != 0:
      fCols.append(c)
    elif singleDist(col, cols[c]) < 0:
      return None
    else:
      markCol(board, c)
  return fCols

def fillFulls(board, rows, cols):
  for r in range(len(rows)):
    if len(rows[r]) == 1:
      if rows[r][0] == len(cols):
        for c in range(len(cols)):
          if board[r][c] == ' ':
            board[r][c] = '#'
      
    if sum(rows[r]) + len(rows[r]) - 1 == len(cols):
      i = 0
      for block in rows[r]:
        for c in range(i, i + block):
          if board[r][c] == ' ':
            board[r][c] = '#'
        i += block + 1

  
  for c in range(len(cols)):
    if len(cols[c]) == 1:
      if cols[c][0] == len(rows):
        for r in range(len(rows)):
          if board[r][c] == ' ':
            board[r][c] = '#'

    if sum(cols[c]) + len(cols[c]) - 1 == len(rows):
      i = 0
      for block in cols[c]:
        for r in range(i, i + block):
          if board[r][c] == ' ':
            board[r][c] = '#'
        i += block + 1


      
  return

def squash(options):
  out = []
  for i in range(len(options[0])):
    col = []
    for j in options:
      col.append(j[i])
    if col == [col[0]]*len(col):
      out.append(col[0])
    else:
      out.append(' ')
  return out

def findSimilarRow(board, rowIDx, row, options):
  out = []
  for o in options:
    similar = True
    for i in range(len(board[0])):
      if board[rowIDx][i] == o[i]:
        continue
      if board[rowIDx][i] != ' ':
        similar = False
        break
    if similar:
      out.append(o)
  return out

def findSimilarCol(board, colIDx, col, options):
  out = []
  for o in options:
    similar = True
    for i in range(len(board)):
      if board[i][colIDx] == o[i]:
        continue
      if board[i][colIDx] != ' ':
        similar = False
        break
    if similar:
      out.append(o)
  return out

def reviewPossibleRows(board, rows, fRows, rowOptions):
  for r in fRows:
    options = rowOptions[r]
    options = findSimilarRow(board, r, rows[r], options)
    if len(options) == 0:
      return None
    options = squash(options)
    for i in range(len(board[r])):
      if board[r][i] == ' ':
        board[r][i] = options[i]
    
  return 1

def reviewPossibleCols(board, cols, fCols, colOptions):
  for c in fCols:
    options = colOptions[c]
    options = findSimilarCol(board, c, cols[c], options)
    if len(options) == 0:
      return None
    options = squash(options)
    for i in range(len(board)):
      if board[i][c] == ' ':
        board[i][c] = options[i]
  return 1

def findBlock(row, b):
  idx = []
  if row[:b] == ['#']*b and row[b] == ' ':
    idx.append(0)
  
  for i in range(1, len(row) - b - 1):
    if row[i:i+b] == ['#']*b:
      if row[i-1] != ' ' or row[i+b] == ' ':
        continue
      idx.append(i)
  
  if row[-b:] == ['#']*b and row[-b-1] == ' ':
    idx.append(len(row) - b)

  return idx

def expandRows(board, rows, fRows):
  for r in fRows:
    if len(rows[r]) == 1:
      block = rows[r][0]
      dots = [i for i, x in enumerate(board[r]) if x == '.']
      if len(dots) == 0:
        continue
      if dots[0]+1 <= block: # can the block fit in the beginning
        for i in range(dots[0]):
          board[r][i] = '.'
      
      for i in range(len(dots) - 1):
        if dots[i+1] - dots[i] <= block:
          for j in range(dots[i], dots[i] + block):
            if j < len(board[r]):
              break
            board[r][j] = '.'

      if len(board[0]) - dots[-1] <= block:
        for i in range(dots[-1], len(board[r])):
          board[r][i] = '.'
  return

def expandCols(board, cols, fCols):
  for c in fCols:
    # filling holes
    if len(cols[c]) == 1:
      block = cols[c][0]
      
      col = []
      for r in range(len(board)):
        col.append(board[r][c])
      
      dots = [i for i, x in enumerate(col) if x == '.']
      if len(dots) == 0:
        continue
      if dots[0]+1 <= block: # can the block fit in the beginning
        for i in range(dots[0]):
          board[i][c] = '.'
      
      for i in range(len(dots) - 1):
        if dots[i+1] - dots[i] <= block:
          for j in range(dots[i], dots[i] + block):
            if j < len(board):
              break
            board[j][c] = '.'
      
      if len(board) - dots[-1] <= block:
        for i in range(dots[-1], len(board)):
          board[i][c] = '.'
  
    # filling unused spaces
    # col = []
    # for r in range(len(board)):
    #   col.append(board[r][c])
    # for block in cols[c]:
    #   blocks = findBlock(col, block)

  return

def printBoard(board):
  for row in board:
    print(row)
  return

def solve(board, rows, cols, rowOptions, colOptions):
  board = [ i.copy() for i in board ]

  fRows = failedRows(board, rows)
  fCols = failedCols(board, cols)

  prevBoard = str(board)

  while len(fRows) > 0  and len(fCols) > 0:
    if DEBUG:
      printBoard(board)
      print("-------------------")
      input()

    ret = reviewPossibleRows(board, rows, fRows, rowOptions)
    if ret == None:
      return None
    
    ret = reviewPossibleCols(board, cols, fCols, colOptions)
    if ret == None:
      return None

    expandRows(board, rows, fRows)
    expandCols(board, cols, fCols)

    fRows = failedRows(board, rows)
    fCols = failedCols(board, cols)
    if fRows == None or fCols == None:
      return None

    if prevBoard == str(board):
      i = 0
      j = 0
      for f in fRows:
        try:
          j = board[f].index(' ')
        except:
          continue
        i = f
        break

      board[i][j] = '#'
      retBoard = solve(board, rows, cols, rowOptions, colOptions)
      if retBoard == None:
        board[i][j] = '.'
        retBoard = solve(board, rows, cols, rowOptions, colOptions)
      
      if retBoard == None:
        return None

      board = retBoard

    prevBoard = str(board)

  return board


def main():
  input_file = open('zad_input.txt', 'r')
  output_file = open('zad_output.txt', 'w')

  (x, y) = input_file.readline().strip().split(" ")
  x = int(x)
  y = int(y)

  board = [[' ' for i in range(y)] for j in range(x)]
  rows = [[] for i in range(x)]
  cols = [[] for i in range(y)]
  fRows = []
  fCols = []


  for line in range(x):
    l = input_file.readline().strip().split(" ")
    for i in l:
      rows[line].append(int(i))

  for line in range(y):
    l = input_file.readline().strip().split(" ")
    for i in l:
      cols[line].append(int(i))

  input_file.close()

  fillFulls(board, rows, cols)

  rowOptions = [ permutate(board[i], rows[i]) for i in range(len(rows)) ]
  colOptions = [ permutate([board[j][i] for j in range(len(board))], cols[i]) for i in range(len(cols)) ]

  board = solve(board, rows, cols, rowOptions, colOptions)
    
  for i in range(len(rows)):
    for j in range(len(cols)):
      output_file.write(board[i][j])
    output_file.write('\n')
  output_file.close()
  return

if __name__ == "__main__":
  main()