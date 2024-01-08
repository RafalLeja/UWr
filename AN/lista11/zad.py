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

def iloczyn(*args):
    wynik = 0
    for i in range(len(args[0])):
        iloczyn = 1
        for arg in args:
            iloczyn *= arg[i]
        wynik += iloczyn
    return wynik

def aproksymacja_sredniokwardratowa(x, n, xk, yk):
    wynikiWielomianow = []
    wynikiDlaX = []
    # P0 = 1
    wynikiWielomianow.append(list(np.ones(len(xk))))
    wynikiDlaX.append(1)
    # P1 = x - c1
    c1 = sum(xk)/len(xk)
    wynikiWielomianow.append([xk[i] - c1 for i in range(len(xk))])
    wynikiDlaX.append((x-c1))
    xQkQk = 0
    QkQk = 0
    prevQkQk = iloczyn(wynikiWielomianow[0], wynikiWielomianow[0])
    for i in range(2, n+1):
        xQkQk = iloczyn(xk, wynikiWielomianow[i-1], wynikiWielomianow[i-1])
        QkQk = iloczyn(wynikiWielomianow[i-1], wynikiWielomianow[i-1])
        ck = xQkQk/QkQk
        dk = QkQk/prevQkQk
        Qk = [(xk[j] - ck)*wynikiWielomianow[i-1][j] - dk*wynikiWielomianow[i-2][j] for j in range(len(xk))]
        wynikiWielomianow.append(Qk)
        wynikiDlaX.append((x - ck)*wynikiDlaX[i-1] - dk*wynikiDlaX[i-2])
        prevQkQk = QkQk

    # print(wynikiWielomianow)
    # print(wynikiDlaX)
        
    wspolczynniki = []
    for i in range(n+1):
        licz = iloczyn(yk, wynikiWielomianow[i])
        mian = iloczyn(wynikiWielomianow[i], wynikiWielomianow[i])
        wspolczynniki.append(licz/mian)

    # print(wspolczynniki)

    wynikKoncowy = 0
    for i, a in enumerate(wspolczynniki):
        wynikKoncowy += a*wynikiDlaX[i]
    return wynikKoncowy



# Zadanie 1
# Wczytaj dane z pliku do obiektu DataFrame
# i narysuj wykres.
df = pd.read_csv('./punkty.csv', sep=',', names=['x', 'y'])
df = df.sort_values(by=['x'])

# aproksymacja_sredniokwardratowa(0, 2, [-9, -6, 0, 6, 9], [-3, 4, -2, 4, -3])
plt.scatter(df['x'], df['y'])
Xpoints = np.linspace(min(df['x']), max(df['x']), 300)
plt.ylim(-5, 90)
plt.plot(Xpoints, f(Xpoints), color='red')
# plt.plot(Xpoints, Lagrange(Xpoints, df['x'], df['y']), color='green')
for n in range(2, 15):
    plt.plot(Xpoints, aproksymacja_sredniokwardratowa(Xpoints, n, df['x'], df['y']))
plt.show()
