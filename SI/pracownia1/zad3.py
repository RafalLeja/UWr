import random

def toDict(List):
  Dict = {}
  for i in List:
    if i in Dict:
      Dict[i] += 1
    else:
      Dict[i] = 1
  return Dict

def LosFigury(Fig):
  talia = [ (11, 'S'), (11, 'H'), (11, 'D'), (11, 'C'),
            (12, 'S'), (12, 'H'), (12, 'D'), (12, 'C'),
            (13, 'S'), (13, 'H'), (13, 'D'), (13, 'C'),
            (14, 'S'), (14, 'H'), (14, 'D'), (14, 'C') ]

  for i in range(5):
    r = random.randint(0, len(talia)-i-1)
    Fig.append(talia[r])
    talia.pop(r)
  return Fig

def LosBlotek(Blot):
  talia = [(2, 'S'), (2, 'H'), (2, 'D'), (2, 'C'),
           (3, 'S'), (3, 'H'), (3, 'D'), (3, 'C'),
           (4, 'S'), (4, 'H'), (4, 'D'), (4, 'C'),
           (5, 'S'), (5, 'H'), (5, 'D'), (5, 'C'),
           (6, 'S'), (6, 'H'), (6, 'D'), (6, 'C'),
           (7, 'S'), (7, 'H'), (7, 'D'), (7, 'C'),
           (8, 'S'), (8, 'H'), (8, 'D'), (8, 'C'),
           (9, 'S'), (9, 'H'), (9, 'D'), (9, 'C'),
           (10, 'S'), (10, 'H'), (10, 'D'), (10, 'C')]

  for i in range(5):
    r = random.randint(0, len(talia)-i-1)
    Blot.append(talia[r])
    talia.pop(r)
  return Blot

def LosBlotek2(Blot):
  talia = [(8, 'S'), (8, 'H'), (8, 'D'), (8, 'C'),
           (9, 'S'), (9, 'H'), (9, 'D'), (9, 'C'),
           (10, 'S'), (10, 'H'), (10, 'D'), (10, 'C')]

  for i in range(5):
    r = random.randint(0, len(talia)-i-1)
    Blot.append(talia[r])
    talia.pop(r)
  return Blot

def ranking(Fig, Blot):
  Fig = sorted(Fig, key=lambda x: x[0], reverse=True)
  Blot = sorted(Blot, key=lambda x: x[0], reverse=True)
  F = toDict(map(lambda x: x[0], Fig))
  F = sorted(F.items(), key=lambda x: x[1], reverse=True)
  B = toDict(map(lambda x: x[0], Blot))
  B = sorted(B.items(), key=lambda x: x[1], reverse=True)
  fRank = 0
  bRank = 0
  if F[0][1] == 4: # kareta
    fRank = 7
  elif F[0][1] == 3 and F[1][1] == 2: # full
    fRank = 6
  elif Fig[0][1] == Fig[1][1] == Fig[2][1] == Fig[3][1] == Fig[4][1]: # kolor
    fRank = 5
  elif F[0][1] == 3: # trojka
    fRank = 3
  elif F[0][1] == 2 and F[1][1] == 2: # dwie pary
    fRank = 2
  elif F[0][1] == 2: # para
    fRank = 1
  else:
    fRank = 0
  if Blot[0][0] == Blot[1][0] - 1 == Blot[2][0] - 2 == Blot[3][0] - 3 == Blot[4][0] - 4: # strit
    if Blot[0][1] == Blot[1][1] == Blot[2][1] == Blot[3][1] == Blot[4][1]: # poker
      bRank = 8
    else:
      bRank = 4
  elif B[0][1] == 4: # kareta
    bRank = 7
  elif B[0][1] == 3 and B[1][1] == 2: # full
    bRank = 6
  elif Blot[0][1] == Blot[1][1] == Blot[2][1] == Blot[3][1] == Blot[4][1]: # kolor
    bRank = 5
  elif B[0][1] == 3: # trojka
    bRank = 3
  elif B[0][1] == 2 and B[1][1] == 2: # dwie pary
    bRank = 2
  elif B[0][1] == 2: # para
    bRank = 1
  else:
    bRank = 0
  # print("Figurant: ", Fig, fRank, "Blotkarz: ", Blot, bRank)
  if fRank >= bRank: # gdy figury sa rowne figurant ma przewage 
    return (1, 0)
  elif fRank < bRank:
    return (0, 1)

def main():
  N = 50000
  Fig = []
  Blot = []
  punktyF = 0
  punktyB = 0
  for i in range(N):
    LosFigury(Fig)
    LosBlotek2(Blot)
    (fP, bP) = ranking(Fig, Blot)
    punktyF += fP
    punktyB += bP
    Fig = []
    Blot = []

  print("Figurant: ", punktyF, "Blotkarz: ", punktyB, "Szansa na wygrana Blotkarza: ", punktyB/N)
  return 

if __name__ == "__main__":
  main()