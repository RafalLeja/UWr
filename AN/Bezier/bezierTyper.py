from PIL import Image, ImageDraw
import numpy as np
import utils

def read_curves(src):
  filename = src
  if filename == ():
    return

  file = open(filename, "rt")
  beziers = []
  nifs = []
  colors = []
  pX, pY = [], []
  width = []
  type_name = ""
  idx = 0
  for line in file.readlines():
    if line[0] == "\"":
      if idx > 0:
        points = np.array([[pX[i], pY[i]] for i in range(len(pX))])
        if type_name == "bezier":
          beziers.append(points)
        elif type_name == "NIFS3":
          nifs.append([pX, pY])
        elif type_name == "Kolor":
          for i in range(len(pX)):
            colors.append([pX[i], pY[i]])

      nameStart = line.find("\"")
      nameEnd = line.find("\"", nameStart+1)
      name = line[nameStart+1:nameEnd]
      typeStart = line.find("\"", nameEnd+1)
      typeEnd = line.find("\"", typeStart+1)
      type_name = line[typeStart+1:typeEnd]
      idx += 1
      continue
    if line[:3] == "  X":
      pX = []
      for l in line[8:-2].split(", "):
        pX.append(int(l))
      continue
    if line[:3] == "  Y":
      pY = []
      for l in line[8:-2].split(", "):
        pY.append(int(l))
      continue
    if line[0] == "w":
      for l in line[7:].split(","):
        width.append(int(l))
      continue

  points = np.array([[pX[i], pY[i]] for i in range(len(pX))])
  if type_name == "bezier":
    beziers.append(points)
  elif type_name == "NIFS3":
    nifs.append([pX, pY])
  elif type_name == "Kolor":
    for i in range(len(pX)):
      colors.append([pX[i], pY[i]])

  file.close
  return [beziers, nifs, colors, width]

def draw_letter(letter, img, start, color):
  RES = 1000
  beziers, nifs, colors, width = letter
  for b in beziers:
    p = [] 
    for i in range(RES):
      p.append(tuple(list(utils.casteljau(i/RES, b))))
      p[i]=tuple([p[i][0]+start[0], p[i][1]+start[1]])
    img.line(p, fill=color, width=1)
  for n in nifs:
    mX = utils.interpolMatrix(n[0])
    mY = utils.interpolMatrix(n[1])
    p = []
    for i in range(0, RES+1):
      p.append(utils.interpolValue(i/RES, n[0], mX)+start[0])
      p.append(utils.interpolValue(i/RES, n[1], mY)+start[1])
    img.line(*p, fill=color, width=1)



def main():
  letter_width = 800
  letter_height = 800
  total_width = 0
  separator = 0
  text = "aA a a AAa"
  src = "./litery"

  text = text.upper()
  letters = dict()
  for i in text:
    if i == " ":
      total_width += letter_width
      continue
    if i not in letters.keys():
      letters[i] = read_curves(src+"/"+i+".txt")

    total_width += separator + letters[i][3][1] - letters[i][3][0]

  with Image.new("RGB", (total_width, letter_height), (255, 255, 255)) as img:
    start = [0, 0]
    d = ImageDraw.Draw(img)
    for i in text:
      if i == " ":
        start[0] += 800 + separator
        continue
     
      draw_letter(letters[i], d, start, (0, 0, 0))
      for c in letters[i][2]:
        nc = tuple([c[0] + start[0], c[1]])
        ImageDraw.floodfill(img, nc, (0, 0, 0))

      start[0] += separator + letters[i][3][1] - letters[i][3][0]

    img.save("./wyraz.png")


if __name__ == "__main__":
  main()