from PIL import Image, ImageDraw
import numpy as np

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

def casteljau(t, points):
  n = len(points)-1
  s=1-t
  b=n
  d=t
  p=points[0]
  for i in range(1, n+1):
    p = p*s + points[i]*d*b
    d *= t
    b = b*(n-i)/(i+1)
  return p*1

def interpolMatrix(values):
  n = len(values) -1
  points = [i/n for i in range(len(values))]


  q = np.zeros(n)
  u = np.zeros(n)
  p = np.zeros(n)
  m = np.zeros(n+1)


  def h(k):
    return points[k] - points[k-1]

  def lam(k):
    return h(k)/(h(k)+h(k+1))

  def f(a, b):
    if a == b:
      return values[a]
    return (f(a+1, b) - f(a, b-1))/(points[b]-points[a])

  def d(k):
    return 6*f(k-1, k+1)

  for k in range(1, n):
    p[k] = 2 + (q[k-1]*lam(k))
    q[k] = (lam(k)-1)/p[k]
    u[k] = (d(k)-lam(k)*u[k-1])/p[k]

  m[n-1] = u[n-1]

  for k in range(n-2, 0, -1):
    m[k] = u[k] + q[k]*m[k+1]

  return m

def interpolValue(x, values, m):
  n = len(values) - 1
  points = [i/n for i in range(len(values))]

  def h(k):
    return points[k] - points[k-1]

  for i in range(1, n+1):
    if points[i-1] <= x and x < points[i]:
      break

  a = (m[i-1]*((points[i] - x)**3))/6
  b = (m[i]*((x - points[i-1])**3))/6
  c = (values[i-1] - (m[i-1]*(h(i)**2)/6))*(points[i] - x)
  d = (values[i] - (m[i]*(h(i)**2)/6))*(x - points[i-1])
  s = (a + b + c + d)/h(i)

  return s

def draw_letter(letter, img, start, color):
  RES = 1000
  beziers, nifs, colors, width = letter
  for b in beziers:
    p = [] 
    for i in range(RES):
      p.append(tuple(list(casteljau(i/RES, b))))
      p[i]=tuple([p[i][0]+start[0], p[i][1]+start[1]])
    img.line(p, fill=color, width=1)
  for n in nifs:
    mX = interpolMatrix(n[0])
    mY = interpolMatrix(n[1])
    p = []
    for i in range(0, RES+1):
      p.append(interpolValue(i/RES, n[0], mX)+start[0])
      p.append(interpolValue(i/RES, n[1], mY)+start[1])
    img.line(*p, fill=color, width=1)



def main():
  letter_width = 800
  letter_height = 800
  total_width = 0
  separator = 0
  text = "aA a a AAa"
  src = "C:/Users/rafal/Desktop/UWr/AN/Bezier/litery"

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

    img.save("C:/Users/rafal/Desktop/UWr/AN/Bezier/wyraz.png")


if __name__ == "__main__":
  main()