import math
import numpy as np


def f(x):
    return (2024*x**8)-(1977*x**4)-1981

def h(x):
    return 1/(1+x**2)

def g(x):
    return math.sin(5*x-math.pi/3)

def i(x):
    arr = [1, 2, 2, 0, 1]
    return arr[int(x*4)]

# def T(i, fn, a, b):
#     h = (b-a)/(2**i)
#     tn = [a + i*h for i in range(2**i+1)]
#     sum = 0
#     for j in range(2**i):
#         sum += (fn(tn[j])+fn(tn[j+1]))/2
#     return h*sum

def quickM(n, fn, a, b):
    h = (b-a)/n
    sum = 0
    for i in range(1, n):
        sum += fn(a+(2*i-1)*h*0.5)
    return h*sum

def Romberg(fn, a, b, n):
    tablica = [[0 for i in range(n+1)] for j in range(n+1)]

    tablica[0][0] = (b-a)*(fn(a)+fn(b))/2

    for i in range(1, n+1):
        tablica[0][i] = 0.5*(tablica[0][i-1] + quickM(2**(i-1), fn, a, b))

    for col in range(1,n+1):
        for row in range(col, n+1):
            tablica[col][row] = (4**col * tablica[col-1][row] - tablica[col-1][row-1]) / (4**col-1)
    
    return tablica[-1][-1]

# tab1 = Romberg(h, -3, 3, 20)
# for x in range(len(tab1)):
#     for y in range(len(tab1[0])):
#         print(format(tab1[y][x], "f"), end=", ")
#     print("\n")

print(f"a) = {Romberg(f, -3, 2, 20)}")
print(f"b) = {Romberg(h, -3, 3, 20)}")
print(f"c) = {Romberg(g, -3*math.pi, math.pi/6, 20)}")
