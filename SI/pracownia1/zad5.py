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

  print(x, y, rows, cols)
  return

if __name__ == "__main__":
  main()
