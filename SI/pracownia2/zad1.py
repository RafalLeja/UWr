import random
from itertools import combinations

DEBUG = True
  
def opt_dist(L, D):
  min = len(L)
  idx = []
  start = 0
  end = D
  mask = ['#']*D
  while end <= len(L):
    bits = listXor(L[start:end], mask)
    bits += listClear(L, start, end)
    if bits < min:
      min = bits
    if bits == min:
      idx.append(start)
    start += 1
    end += 1
  return (min, idx)

def listXor(L1, L2):
  if len(L1) != len(L2):
    return -1
  bits = 0
  for i in range(len(L1)):
    if L1[i] != L2[i]:
      bits += 1
  return bits

def listClear(L, s, e):
  bits = 0
  for i in L[:s]:
    if i == '#':
      bits += 1
  for i in L[e:]:
    if i == '#':
      bits += 1
  return bits

def failedRows(board, rows):
  fRows = []
  for r in range(len(rows)):
    s = 0
    for c in range(len(board[r])):
      if board[r][c] == '#':
        s += 1
    if s < rows[r][0] or s < sum(rows[r]) + len(rows[r]) - 1:
      fRows.append(r)
  return fRows

def failedCols(board, cols):
  fCols = []
  for c in range(len(cols)):
    s = 0
    for r in range(len(board)):
      if board[r][c] == '#':
        s += 1
    if s < cols[c][0] or s < sum(cols[c]) + len(cols[c]) - 1:
      fCols.append(c)
  return fCols

def fillFulls(board, rows, cols, rowsLeft, colsLeft):
  for r in range(len(rows)):
    if len(rows[r]) == 1:
      if rows[r][0] == len(rows):
        for c in range(len(cols)):
          if board[r][c] == '.':
            board[r][c] = '#'
            # colsLeft[c] -= 1
        rowsLeft[r] = 0
      
    if sum(rows[r]) + len(rows[r]) - 1 == len(rows):
      i = 0
      for block in rows[r]:
        for c in range(i, i + block):
          if board[r][c] == '.':
            board[r][c] = '#'
            # colsLeft[c] -= 1
        i += block + 1
      rowsLeft[r] = [0]
  
  for c in range(len(cols)):
    if len(cols[c]) == 1:
      if cols[c][0] == len(cols):
        for r in range(len(rows)):
          if board[r][c] == '.':
            board[r][c] = '#'
            # rowsLeft[r] -= 1
        colsLeft[c] = [0]

    if sum(cols[c]) + len(cols[c]) - 1 == len(cols):
      i = 0
      for block in cols[c]:
        for r in range(i, i + block):
          if board[r][c] == '.':
            board[r][c] = '#'
            # rowsLeft[r] -= 1
        i += block + 1
      colsLeft[c] = [0]
      
  return

def columnCheck(board, opt, r, rows, colsLeft):
  filtered = []
  for start in opt:
    good = True
    for c in range(rows[r]):
      if colsLeft[c+start] == 0 and board[r][c+start] != '#':
        good = False
        break
    if good:
      filtered.append(start)
  return filtered

def findSpots(board, rows, fRows, colsLeft):
  optRows = []
  for r in fRows:
    opt = opt_dist(board[r], rows[r])[1]
    opt = columnCheck(board, opt, r, rows, colsLeft)
    opt = sorted(opt, key = lambda x: min(colsLeft[x:x+rows[r]]))
    if len(opt) > 0:
      optRows.append(opt)
    else:
      fRows.remove(r)
  return optRows
    
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
  
def permutate(board, row):
  options = []
  # print(board, row)
  n = len(board) - sum(row) - len(row) + 1
  block_idx = list(combinations(range(n+len(row)), len(row)))
  print(list(block_idx))
  for idx in block_idx:
    options.append(generateRow(row, idx, n))
  # options = generateRow(row, block_idx[0])
  return options

def reviewPossibleRows(board, rows, fRows):
  for r in fRows:
    options = permutate(board[r], rows[r])
    if len(options) == 0:
      fRows.remove(r)
      continue
    
  return


def printBoard(board):
  for row in board:
    print(row)
  return

def main():
  input_file = open('zad_input.txt', 'r')
  output_file = open('zad_output.txt', 'w')

  (x, y) = input_file.readline().strip().split(" ")
  x = int(x)
  y = int(y)
  board = [['.' for i in range(y)] for j in range(x)]
  rows = [[] for i in range(x)]
  cols = [[] for i in range(y)]
  rowsLeft = []
  colsLeft = []
  fRows = []
  fCols = []
  optRows = []

  for line in range(x):
    l = input_file.readline().strip().split(" ")
    for i in l:
      rows[line].append(int(i))

  for line in range(y):
    l = input_file.readline().strip().split(" ")
    for i in l:
      cols[line].append(int(i))

  # print(rows)
  # print(cols)

  input_file.close()

  rowsLeft = rows.copy()
  colsLeft = cols.copy()

  # fillFulls(board, rows, cols, rowsLeft, colsLeft)

  printBoard(board)

  fRows = failedRows(board, rows)
  fCols = failedCols(board, cols)

  reviewPossibleRows(board, rows, fRows)

  # optRows = findSpots(board, rows, fRows, colsLeft)

  # while len(fRows) > 0  and len(fCols) > 0:
  #   if DEBUG:
  #     for i in range(len(rows)):
  #       print(rows[i], rowsLeft[i], board[i])
  #     print("      ", end = '')

  #     for i in range(len(cols)):
  #       print(colsLeft[i], "   ", end = '')
  #     print()

  #     print("      ", end = '')
  #     for i in range(len(cols)):
  #       print(cols[i], "   ", end = '')
        
  #     print()
  #     print(optRows)
  #     print(fRows)
  #     print(fCols)
  #     print("-------------------")
  #     input()

  #   r = max(fRows, key = lambda x: rowsLeft[x])
  #   # print(r, optRows)
  #   c = optRows[fRows.index(r)][0]

  #   for i in range(rows[r]):
  #     if board[r][c+i] == '.':
  #       board[r][c+i] = '#'
  #       rowsLeft[r] -= 1

  #   colsLeft[c] -= 1
  #   fRows = failedRows(board, rows)
  #   fCols = failedCols(board, cols)
  #   optRows = findSpots(board, rows, fRows, colsLeft)
    
  # for i in range(len(rows)):
  #   for j in range(len(cols)):
  #     output_file.write(board[i][j])
  #   output_file.write('\n')
  # output_file.close()
  # return

if __name__ == "__main__":
  main()