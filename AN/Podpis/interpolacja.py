import matplotlib.pyplot as plt
import numpy as np

HEIGHT = 246
WIDTH = 1562


Nx = [ 157, 136, 151, 108, 50, 48, 52]
Ny = [ 101, 84, 170, 186, 100, 197, 108]

Ux = [ 187, 198, 235, 234]
Uy = [ 128, 191, 178, 131]

Mx = [ 265, 269, 283, 294, 312, 317, 331]
My = [ 129, 167, 136, 155, 140, 153, 164]

ERx = [ 356, 390, 384, 370, 407, 421, 424, 449]
ERy = [ 142, 152, 124, 166, 166, 132, 177, 126]

KIx = [ 478, 471, 500, 509, 511, 547, 553, 550, 557]
KIy = [ 84, 155, 155, 126, 168, 150, 115, 144, 166]

KROPKAx = [ 566, 574, 569]
KROPKAy = [ 84, 90, 83]

Sx = [ 720, 706, 699, 725, 752, 700]
Sy = [ 110, 104, 118, 136, 152, 158]

Ax = [ 774, 780, 805, 794, 829, 810, 844]
Ay = [ 109, 138, 129, 114, 149, 183, 189]

SUx = [ 981, 999, 1012, 990, 1038, 1040, 1052, 1072, 1076]
SUy = [ 103, 125, 152, 147, 119, 110, 139, 134, 104]

Px = [ 1104, 1114, 1109, 1085, 1092, 1118, 1143, 1116]
Py = [ 104, 135, 207, 221, 156, 97, 110, 151]

ER2x = [ 1164, 1195, 1195, 1167, 1194, 1241, 1241, 1282]
ER2y = [ 112, 121, 94, 126, 146, 92, 137, 89]

OKO1x = [ 1395, 1394, 1402]
OKO1y = [ 83, 93, 90]

OKO2x = [ 1395, 1406, 1404]
OKO2y = [ 125, 128, 121]

NOSx = [ 1422, 1444]
NOSy = [ 104, 103]

USTAx = [ 1452, 1470, 1459]
USTAy = [ 65, 101, 136]

litery = [[Nx, Ny], [Ux, Uy], [Mx, My], [ERx, ERy], [KIx, KIy], [KROPKAx, KROPKAy], [Sx, Sy],
          [Ax, Ay], [SUx, SUy], [Px, Py], [ER2x, ER2y], [OKO1x, OKO1y], [OKO2x, OKO2y], [NOSx, NOSy], [USTAx, USTAy]]

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

M = 1000
fig, ax = plt.subplots(figsize=(6.36, 1.04))
ax = fig.add_axes((0, 0, 1, 1))
ax.set(ylim=(0,HEIGHT),       
       xlim=(0,WIDTH),
       yticks=[],
       xticks=[])
ax.invert_yaxis()
       
out = open("dane.txt", "wt")

itr = 0
for litera in litery:

  literaX = []
  literaY = []
  
  mx = interpolMatrix(litera[0])
  my = interpolMatrix(litera[1])
  for i in range(0, M+1):
    literaX.append(interpolValue(i/M, litera[0], mx))
    literaY.append(interpolValue(i/M, litera[1], my))

  ax.plot(literaX, literaY, color='blue', linewidth=0.8)
  out.write(f'''krzywa{itr}:\n
            Xn = {litera[0]}\n
            Yn = {litera[1]}\n
            tn = {[k/len(litera[0]) for k in range(len(litera[0]))]}\n
            un = {[k/M for k in range(M)]}\n\n''')
  itr +=1


fig.savefig("output.png")

