import math
import matplotlib.pyplot as plt
import numpy as np


def f(x):
    return 2024*x**8-1977*x**4-1981

def h(x):
    return 1/(1+x**2)

def g(x):
    return math.sin(5*x-math.pi/3)

def i(x):
    return x**2

def Romberg(fn, a, b, n):
    space = np.linspace(a, b, 100)
    plt.plot(space, [fn(x) for x in space], color='red')
    h = (b-a)/n
    tn = [a + i*h for i in range(n+1)]
    sum = 0
    for i in range(len(tn)-1):
        plt.plot([tn[i], tn[i+1]], [fn(tn[i]), fn(tn[i+1])], color='blue')
        sum += h*(fn(tn[i]) + fn(tn[i+1]))/2
    plt.show()
    return sum

print(Romberg(h, -3, 3, 15))