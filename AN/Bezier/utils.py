# Rafał Leja 340879
# konkurs 2 ANL

import numpy as np

# algorytm z ćwiczeń
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

# algorytm z wykładu
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