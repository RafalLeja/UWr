import matplotlib.pyplot as plt
import numpy as np
import math

points = np.array([(0, 0), (3.5, 36), (25, 25), (25, 1.5), (-5, 3), (-5, 33),
(15, 11), (-0.5, 35), (19.5, 15.5), (7, 0), (1.5, 10.5)])

weights = [1, 6, 4, 2, 3, 4, 2, 1, 5, 4, 1]
weights2 = [1, 6, 4, 2, 3, 8, 4, 2, 10, 8, 2]
weights3 = [1, 6, 4, 2, 3, 4, 100, 1, 5, 4, 1]
ones = np.ones(len(points))

tn = [i/95 for i in range(95)]

# function eval_horner(t) { 
#   u = 1 - t;
#   bc = 1;
#   tn = 1;
#   tmp = controlpoints[0] * u;
#   for(int i = 1; i < n; i++) {
#     tn *= t;
#     bc *= (n-i+1)/i;
#     tmp = (tmp + tn * bc * controlpoints) * u;
#   } 
#     return (tmp + tn * t * controlpoints[n]);


# def de_casteljau(t, points):
#   p = points.copy()
#   n = len(p)
#   for i in range(1, n):
#     for j in range(n-i):
#       p[j] = (1-t)*p[j] + t*p[j+1]

#   return p[0]

def B(n, i, t):
  newton = math.comb(n, i)
  return newton*(t**i)*((1-t)**(n-i))

def krzywa(t, w, p):
  n = len(p)-1
  licz = 0
  mian = 0
  for i in range(0, n):
    # print(i/M)
    bern = B(n, i, t)
    licz += w[i]*p[i]*bern
    mian += w[i]*bern
  return licz/mian


M = 1000
curveX =[]
curveY = []
bX = []
bY = []
for i in range(0, M+1):
  p = krzywa(i/M, weights, points)
  curveX.append(p[0])
  curveY.append(p[1])
  p2 = krzywa(i/M, weights3, points)
  bX.append(p2[0])
  bY.append(p2[1])
# print(krzywa(1/2, weights, points))
plt.xlim(0, 35)
plt.ylim(0, 35)
plt.scatter(points[:,0], points[:,1])
plt.plot(bX, bY, color="blue")
plt.plot(curveX, curveY, color="orange")
# plt.scatter(points[:, 0], points[:, 1])
plt.show()
