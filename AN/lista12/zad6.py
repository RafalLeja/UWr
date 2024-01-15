import numpy as np
import math

# def newton_cotes_coefficients(n):
#     # prarametry dla int0_1
#     x = np.linspace(0, 1, n)
#     calki = np.zeros(n)
#     for i in range(n):
#         calki[i] = 1 / (i+1)
#     Aix = np.zeros((n, n))
#     for j in range(n):
#         for i in range(n):
#             Aix[j][i] = x[i]**j
#     param = np.linalg.solve(Aix, calki)
#     return param

# def newton_cotes(fn, a, b, n):
#     coefficients = newton_cotes_coefficients(n)
#     arr = []
#     for i in range(n):
#         arr.append(((-1)**(2*(n-i)))/math.factorial(i))
#     h = 1 / n
#     result = 0
#     for i in range(n):
#         x = i*h
#         result += coefficients[i] * fn(x*(b-a)+a)
#     return (b-a)*result

def newton_cotes_coefficients_fast(N):
    # prarametry dla int0_1
    xn = np.arange(N+1)
    yi = xn / float(N)
    ti = 2 * yi - 1
    nvec = np.arange(N+1)
    C = ti ** nvec[:, np.newaxis]
    print(C)
    Cinv = np.linalg.inv(C)
    print(Cinv)
    # improve precision of result
    # for i in range(2):
    #     Cinv = 2*Cinv - Cinv.dot(C).dot(Cinv)
    vec = 2.0 / (nvec[::2]+1)
    ai = Cinv[:, ::2].dot(vec) * (N / 2.)

    return ai

def newton_cotes(fn, a, b, n):
    h = (b-a) / n
    coefficients = []
    for i in range(n):
        licz = h*(-1)**(n-i) 
        mian = math.factorial(i)*math.factorial(n-i)

    for i in range(n):
        arr.append(((-1)**(2*(n-i)))/math.factorial(i))
    result = 0
    for i in range(n):
        x = i*h
        result += coefficients[i] * fn(x*(b-a)+a)
    return (b-a)*result

def f(x):
    return 1/(1+25*(x**2))

def g(x):
    return x

for i in range(2, 3):
    print(newton_cotes_coefficients_fast(i))
    # print(f"n={i}, {newton_cotes(g, 0, 5, i)}")
