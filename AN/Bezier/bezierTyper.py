# Rafał Leja 340879
# konkurs 2 ANL

from PIL import Image, ImageDraw, ImageColor
import numpy as np
import utils
import argparse

def read_curves(src):
  filename = src
  try:
    file = open(filename, "rt")
  except OSError as e:
    print(f"Nie można otworzyć {filename}: {e}")
    exit(1)

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
      for l in line[6:].split(","):
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
    img.line(p, fill=color, width=1)

def main():
  argparser = argparse.ArgumentParser()

  argparser.add_argument("-s", "--separator_space", type=int, default=50, help="odstęp między literami")
  argparser.add_argument("-t", "--text", type=str, default="Hello World", help="tekst do napisania")
  argparser.add_argument("-src", "--source", type=str, default="./litery", help="folder z plikami liter")
  argparser.add_argument("-c", "--color", type=str, default="black", help="kolor napisu")
  argparser.add_argument("-bg", "--background", type=str, default="white", help="kolor tła")
  argparser.add_argument("-o", "--output", type=str, default="./napis.png", help="nazwa pliku wyjściowego")
  argparser.add_argument("-i", "--italic", type=bool, default=False, help="czy napis ma być pochylony")

  args = argparser.parse_args()
  
  letter_width = 800
  letter_height = 800
  total_width = 0
  separator = args.separator_space
  text = args.text
  src = args.source
  color = args.color
  background = args.background

  text = text.upper()

  letters = dict()
  if args.italic:
    total_width += 125


  for i in text:
    if i == " ":
      total_width += 600
      continue
    if i not in letters.keys():
      letters[i] = read_curves(src+"/"+i+".txt")
      if args.italic:
        R = 0.4
        midY = letter_height/2
        for line in letters[i][0]:
          for p in line:
            dist = p[1] - midY
            p[0] -= int((dist * R))
        for line in letters[i][1]:
          for p in range(len(line[0])):
            dist = line[1][p] - midY
            line[0][p] -= int((dist * R))
        for j in range(len(letters[i][2])):
          letters[i][2][j][0] -= int((letters[i][2][j][1] - midY) * R)

    total_width += separator + letters[i][3][1] - letters[i][3][0]


  with Image.new("RGB", (total_width, letter_height), background) as img:
    start = [0, 0]
    if args.italic:
      start[0] += 70
    d = ImageDraw.Draw(img)
    for i in text:
      if i == " ":
        start[0] += 600 + separator
        continue
      
      start[0] -= letters[i][3][0]
     
      draw_letter(letters[i], d, start, color)
      for c in letters[i][2]:
        nc = tuple([c[0] + start[0], c[1]])
        ImageDraw.floodfill(img, nc, value=ImageColor.getrgb(color))

      start[0] += separator + letters[i][3][1]

    img.save(args.output)

if __name__ == "__main__":
  main()