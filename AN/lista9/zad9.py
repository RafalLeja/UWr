import matplotlib.pyplot as plt
import numpy as np

points = np.array([(0, 0), (3.5, 36), (25, 25), (25, 1.5), (-5, 3), (-5, 33),
(15, 11), (-0.5, 35), (19.5, 15.5), (7, 0), (1.5, 10.5)])

weights = [1, 6, 4, 2, 3, 4, 2, 1, 5, 4, 1]

w_points = [ points[i]*weights[i] for i in range(len(points))]
print(w_points)

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


def de_casteljau(t, points):
  p = points.copy()
  n = len(p)
  for i in range(1, n):
    for j in range(n-i):
      p[j] = (1-t)*p[j] + t*p[j+1]

  return p[0]


M = 100
curveX =[]
curveY = []
for i in range(M):
  p = de_casteljau(i/M, w_points)
  curveX.append(p[0])
  curveY.append(p[1])
plt.plot(curveX, curveY)
# plt.scatter(points[:, 0], points[:, 1])
plt.show()
