import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import CubicSpline


def interpolMatrix(points, values):
    n = len(values) -1

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

def interpolValue(x, points, values, m):
    n = len(values) - 1

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

# Przykład użycia
points = [-1, 0, 3]
values = [0.5, 0, 3]
m = interpolMatrix(points, values)

# Generowanie punktów do wykresu
x_interp = np.linspace(min(points), max(points), 200)
y_nifs3 = [interpolValue(xi, points, values, m) for xi in x_interp]

# Interpolacja sześciennej funkcji sklejanej z użyciem scipy
cs = CubicSpline(points, values)
y_cubic_spline = cs(x_interp)

# print("-----------")
# print(interpolValue(points[4], points, values, m))
# print(cs(points[0]))

# Wykres porównawczy
plt.plot(x_interp, y_nifs3, label='NIFS3')
plt.plot(x_interp, y_cubic_spline, label='SciPy CubicSpline', linestyle='dashed')
plt.scatter(points, values, color='red', label='Dane wejściowe')
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Porównanie NIFS3 i CubicSpline')
plt.savefig("out.png")
plt.legend()
plt.show()
