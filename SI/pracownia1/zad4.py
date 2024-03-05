# Rafał Leja
# 05.03.2024
# zad4
# Algorytm tworzy maskę o długości D, która jest złożona z samych jedynek. 
# Następnie przesuwa ją po liście L, zliczając ilość bitów różnych od maski.
# W każdym kroku zlicza również ilość bitów różnych od maski, które są poza zakresem maski.
# Wynikiem jest najmniejsza z tych wartości.

def opt_dist(L, D):
  min = len(L)
  start = 0
  end = D
  mask = [1]*D
  while end <= len(L):
    bits = listXor(L[start:end], mask)
    bits += listClear(L, start, end)
    start += 1
    end += 1
    if bits < min:
      min = bits
  return min

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
    if i == 1:
      bits += 1
  for i in L[e:]:
    if i == 1:
      bits += 1
  return bits

def main():
  input_file = open('zad4_input.txt', 'r')
  output_file = open('zad4_output.txt', 'w')
  for line in input_file:
    line = line.strip().split(" ")
    out = opt_dist([int(x) for x in line[0]], int(line[1]))
    output_file.write(str(out) + "\n")
  return

if __name__ == "__main__":
  main()
