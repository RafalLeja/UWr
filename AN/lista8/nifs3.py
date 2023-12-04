import matplotlib.pyplot as plt

xn = [5.5, 8.5, 10.5, 13, 17, 20.5, 24.5, 28, 32.5, 37.5, 40.5, 42.5, 45, 47,
49.5, 50.5, 51, 51.5, 52.5, 53, 52.8, 52, 51.5, 53, 54, 55, 56, 55.5, 54.5, 54, 55, 57, 58.5,
59, 61.5, 62.5, 63.5, 63, 61.5, 59, 55, 53.5, 52.5, 50.5, 49.5, 50, 51, 50.5, 49, 47.5, 46,
45.5, 45.5, 45.5, 46, 47.5, 47.5, 46, 43, 41, 41.5, 41.5, 41, 39.5, 37.5, 34.5, 31.5, 28, 24,
21, 18.5, 17.5, 16.5, 15, 13, 10, 8, 6, 6, 6, 5.5, 3.5, 1, 0, 0, 0.5, 1.5, 3.5, 5, 5, 4.5, 4.5, 5.5,
6.5, 6.5, 5.5]

yn = [41, 40.5, 40, 40.5, 41.5, 41.5, 42, 42.5, 43.5, 45, 47, 49.5, 53, 57, 59,
59.5, 61.5, 63, 64, 64.5, 63, 61.5, 60.5, 61, 62, 63, 62.5, 61.5, 60.5, 60, 59.5, 59, 58.5,
57.5, 55.5, 54, 53, 51.5, 50, 50, 50.5, 51, 50.5, 47.5, 44, 40.5, 36, 30.5, 28, 25.5, 21.5,
18, 14.5, 10.5, 7.50, 4, 2.50, 1.50, 2, 3.50, 7, 12.5, 17.5, 22.5, 25, 25, 25, 25.5, 26.5,
27.5, 27.5, 26.5, 23.5, 21, 19, 17, 14.5, 11.5, 8, 4, 1, 0, 0.5, 3, 6.50, 10, 13, 16.5, 20.5,
25.5, 29, 33, 35, 36.5, 39, 41]

tn = [i/95 for i in range(95)]


def interpolMatrix(points, values):
  n = len(values) - 1
  q = [0 for i in range(n)]
  u = [0 for i in range(n)]
  p = [0 for i in range(n)]
  m = [0 for i in range(n+1)]
  q[0] = 0
  u[0] = 0

  def h(k):
    return points[k] - points[k-1]
  
  def lam(k):
    return h(k)/(h(k)+h(k+1))
  
  def f(a,b):
    if a == b:
      return values[a]
    return (f(a+1,b) - f(a,b-1))/(points[b]-points[a])
  
  def d(k):
    return 6*f(k-1,k+1)

  for k in range(1,n-1):
    p[k] = 2+(q[k-1]*lam(k))
    q[k] = (lam(k)-1)/p[k]
    u[k] = (d(k)-lam(k)*u[k-1])/p[k]
  
  m[n] = 0

  for k in range(n-1,1,-1):
    m[k] = u[k] + q[k]*m[k+1]
  
  return m


def interpolValue(x, points, values, m):
  n = len(values) - 1

  def h(k):
    return points[k] - points[k-1]

  i = n-1
  while x - points[i] < 0:
    i = i-1
  
  a = (m[i+1]-m[i])/(6*h(i))
  b = m[i]/2
  c = (((values[i+1] - values[i])/h(i)) - (h(i)*(m[i+1]+2*m[i])/6))
  s = values[i] + (x-points[i])*(c+(x-points[i])*(b+(x-points[i])*a))
  return s


M = 10000
dogX = [0 for i in range(M)]
dogY = [0 for i in range(M)]
mx = interpolMatrix(tn, xn)
my = interpolMatrix(tn, yn)

for i in range(M):
  dogX[i] = interpolValue(i/M, tn, xn, mx)
  dogY[i] = interpolValue(i/M, tn, yn, my)

plt.plot(dogX, dogY)
plt.show()
