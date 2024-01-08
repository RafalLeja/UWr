import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

def f(x):
    return (x-1.2)*(x+4.7)*(x-2.3)

def Lagrange(x, x_values, y_values):
    wynik = 0
    for i in range(len(x_values)):
        iloczyn = 1
        for j in range(len(x_values)):
            if i != j:
                iloczyn *= (x - x_values[j])/(x_values[i] - x_values[j])
        wynik += y_values[i]*iloczyn
    return wynik

# Zadanie 1
# Wczytaj dane z pliku do obiektu DataFrame
# i narysuj wykres.
df = pd.read_csv('./punkty.csv', sep=',', names=['x', 'y'])
df = df.sort_values(by=['x'])
plt.scatter(df['x'], df['y'])
Xpoints = np.linspace(min(df['x']), max(df['x']), 300)
plt.ylim(-5, 90)
plt.plot(Xpoints, f(Xpoints), color='red')
plt.plot(Xpoints, Lagrange(Xpoints, df['x'], df['y']), color='green')
plt.show()
