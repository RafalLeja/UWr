import random

def LosFigury(Fig):
  talia = [11, 12, 13, 14] # walet, dama, król, as
  talia += talia
  talia += talia # mnożymy przez kolory

  for i in range(5):
    r = random.randint(0, len(talia)-i)
    Fig.append(talia[r])
    talia.pop(r)
  return Fig

def LosBlotek(Blot):
  talia = [2, 3, 4, 5, 6, 7, 8, 9, 10]
  talia += talia
  talia += talia # mnożymy przez kolory

  for i in range(5):
    r = random.randint(0, len(talia)-i)
    Blot.append(talia[r])
    talia.pop(r)
  return Blot

def ranking(Fig, Blot):
  Fig.sort()
  Blot.sort()
  fRank = 0
  bRank = 0
  if Fig[0] == Fig[1] == Fig[2] == Fig[3]: # kareta
    fRank = 8
  elif Fig[0] == Fig[1] == and Fig[3] == Fig[4]: # full


  return

def main():
  N = 1000
  Fig = []
  Blot = []
  for i in range(N):
    LosFigury(Fig)
    LosBlotek(Blot)
    ranking(Fig, Blot)
    Fig = []
    Blot = []
  return 

if __name__ == "__main__":
  main()