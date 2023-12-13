import matplotlib.pyplot as plt

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
  print(m)
  return m

def interpolValue(x, points, values, m):
  n = len(values) - 1

  def h(k):
    return points[k] - points[k-1]

  i = n-1
  while x - points[i] < 0:
    i = i-1

  print(i)
  
  # a = (m[i+1]-m[i])/(6*h(i))
  # b = m[i]/2
  # c = (((values[i+1] - values[i])/h(i)) - (h(i)*(m[i+1]+2*m[i])/6))
  # s = values[i] + (x-points[i])*(c+(x-points[i])*(b+(x-points[i])*a))

  a = (m[i]*((points[i+1] - x)**3))/6
  b = (m[i+1]*((x - points[i+1]-1)**3))/6
  c = (values[i]-(m[i]*(h(i+1)**2)/6))*(points[i+1]-x)
  d = (values[i+1]-(m[i+1]*(h(i+1)**2)/6))*(x-points[i])
  s = (a + b + c + d)/h(i-1)
  return s

x = [-1, 0, 3]
y = [0.5, 0, 3]
points = [i/(len(x)-1) for i in range(len(x))]
M = 2
       
mx = interpolMatrix(points, x)
my = interpolMatrix(points, y)
px=[]
py=[]
for i in range(M+1):
  # print(i)
  px.append(interpolValue(i/M, points, x, mx))
  py.append(interpolValue(i/M, points, y, my))

print(interpolValue(1, points, x, mx))
plt.plot(px, py, color='blue', linewidth=1)
# plt.plot(tn, x, color='blue', linewidth=1)
# plt.plot(tn, y, color='blue', linewidth=1)



plt.show()
