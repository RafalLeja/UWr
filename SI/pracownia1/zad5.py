import opt_dist from zad4

def solved(board, rows, cols):
  for r in rows:
    if opt_dist(board[r], r) != 0:
      return False
  for c in cols:
    if opt_dist(board[c], c) != 0:
      return False

def main():
  input_file = open('zad5_input.txt', 'r')
  output_file = open('zad5_output.txt', 'w')

  (x, y) = input_file.readline().strip().split(" ")
  x = int(x)
  y = int(y)
  rows = []
  cols = []
  board = [[0 for i in range(x)] for j in range(y)]

  for line in range(x):
    rows.append(int(input_file.readline().strip()))

  for line in range(y):
    cols.append(int(input_file.readline().strip()))

  while solved(board, rows, cols) == False:
    print("not solved")
  print(x, y, rows, cols)
  return

if __name__ == "__main__":
  main()