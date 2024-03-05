import random

DEBUG = True

def blockCount(L):
  s = 0
  for i in L:
    if i == '#':
      s += 1
  return s
  
def failedRows(board, rows):
  fRows = []
  for r in range(len(rows)):
    if blockCount(board[r]) != rows[r]:
      fRows.append(r)
  return fRows

def failedCols(board, cols):
  fCols = []
  for c in range(len(cols)):
    col = []
    for r in range(len(board)):
      col.append(board[r][c])
    if blockCount(col) != cols[c]:
      fCols.append(c)
  return fCols

def fillFulls(board, rows, cols, rowsLeft, colsLeft):
  for r in range(len(rows)):
    if rows[r] == len(rows):
      for c in range(len(cols)):
        board[r][c] = '#'
      rowsLeft[r] = 0
      for i in range(len(cols)):
        colsLeft[i] -= 1
  
  for c in range(len(cols)):
    if cols[c] == len(cols):
      for r in range(len(rows)):
        board[r][c] = '#'
      colsLeft[c] = 0
      for i in range(len(rows)):
        rowsLeft[i] -= 1
  return

def main():
  input_file = open('zad5_input.txt', 'r')
  output_file = open('zad5_output.txt', 'w')

  (x, y) = input_file.readline().strip().split(" ")
  x = int(x)
  y = int(y)
  rows = []
  cols = []
  rowsLeft = []
  colsLeft = []
  board = [['.' for i in range(x)] for j in range(y)]
  fRows = []
  fCols = []

  for line in range(x):
    rows.append(int(input_file.readline().strip()))

  for line in range(y):
    cols.append(int(input_file.readline().strip()))

  input_file.close()

  rowsLeft = rows.copy()
  colsLeft = cols.copy()
  fillFulls(board, rows, cols, rowsLeft, colsLeft)
  fRows = failedRows(board, rows)
  fCols = failedCols(board, cols)
  while len(fRows) > 0  and len(fCols) > 0:
    r = max(fRows, key = lambda x: rowsLeft[x])
    c = random.choice(fCols)
    if board[r][c] == '#':
      continue
    board[r][c] = '#'
    rowsLeft[r] -= 1
    colsLeft[c] -= 1
    fRows = failedRows(board, rows)
    fCols = failedCols(board, cols)
    if DEBUG:
      for i in range(len(rows)):
        print(rows[i], rowsLeft[i], board[i])
      print("      ", end = '')

      for i in range(len(cols)):
        print(colsLeft[i], "   ", end = '')
      print()

      print("      ", end = '')
      for i in range(len(cols)):
        print(cols[i], "   ", end = '')
        
      print()
      print(fRows)
      print(fCols)
      input()
    
  for i in range(len(rows)):
    for j in range(len(cols)):
      output_file.write(board[i][j])
    output_file.write('\n')
  output_file.close()
  return

if __name__ == "__main__":
  main()