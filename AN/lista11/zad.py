import pandas as pd
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

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
    # P0 = 1 => czas stały
    wynikiWielomianow.append(list(np.ones(len(xk))))
    wynikiDlaX.append(1)
    # P1 = x - c1 => 5n + 7
    c1 = sum(xk)/len(xk) # 3n + 3 - mnożeń, 2n - dodawań
    wynikiWielomianow.append([xk[i] - c1 for i in range(len(xk))]) # (n+1)
    wynikiDlaX.append((x-c1)) # 1
    xQkQk = 0
    QkQk = 0
    # PK = (x - ck)Qk - dkQk-1 => 
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

    wspolczynniki = []
    for i in range(n+1):
        licz = iloczyn(yk, wynikiWielomianow[i])
        mian = iloczyn(wynikiWielomianow[i], wynikiWielomianow[i])
        wspolczynniki.append(licz/mian)

    wynikKoncowy = 0
    for i, a in enumerate(wspolczynniki):
        wynikKoncowy += a*wynikiDlaX[i]
    return wynikKoncowy

df = pd.read_csv('./punkty.csv', sep=',', names=['x', 'y'])
df = df.sort_values(by=['x'])

fig, ax = plt.subplots()

ax.scatter(df['x'], df['y'])
Xpoints = np.linspace(min(df['x']), max(df['x']), 300)
ax.plot(Xpoints, f(Xpoints), color='red')
fig.savefig('a.png')
ax.cla()

plt.ylim(-5, 90)
ax.scatter(df['x'], df['y'])
ax.plot(Xpoints, Lagrange(Xpoints, df['x'], df['y']), color='green')
fig.savefig('b.png')
ax.cla()

ax.scatter(df['x'], df['y'])
line, = ax.plot([], [], color='green')

def init():
    line.set_data([], [])
    return line,

def update(frame):
    y = aproksymacja_sredniokwardratowa(Xpoints, frame, df['x'], df['y'])
    line.set_data(Xpoints, y)
    fig.legend([line], [f'N = {frame}'])
    return line,

ani = FuncAnimation(fig, update, init_func=init, frames=range(2,16), interval=1000, blit=True)

ani.save('animacja.mp4', writer='ffmpeg', fps=2)

