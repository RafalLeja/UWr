def opt_dist(L, D):
  min = D
  start = 0
  end = D
  mask = [1]*D
  while end < len(L):
    bits = listXor(L[start:end], mask)
    start += 1
    end += 1
    if start - 1 >= 0 and L[start-1] == 1: # trzeba zamienić bit przed startem
      bits += 1
    if end + 1 < len(L) and L[end+1] == 1: # trzeba zamienić bit po end
      bits += 1
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

def main():
  print(opt_dist([0,0,1,0,0,0,1,0,0,0], 2))
  return

if __name__ == "__main__":
  main()
