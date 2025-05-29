import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from scipy import stats

in_file = pd.read_csv("l12z8.csv", sep=",", header=None, names=["X"])

# fake_data = np.random.uniform(0, 1, 1000)
# in_file = pd.DataFrame(fake_data, columns=["X"])

EX = in_file["X"].mean()
VX = in_file["X"].var()
nX = len(in_file["X"])

print("X:")
print("Średnia = ", EX)
print("Wariancja = ", VX)
print("Odchylenie standardowe = ", in_file["X"].std())
print("Liczba próbek = ", nX)
print("\n-----------------------\n")


print("Rozkład normalny:")
print("Metoda Box-Muller")
print("Zdefiniowane zmienne losowe Z_0 i Z_1:")
print("Z_0 = sqrt(-2 * ln(X_0)) * cos(2 * pi * X_1)")
print("Z_1 = sqrt(-2 * ln(X_0)) * sin(2 * pi * X_1)")
# wykres początkowy
# plt.hist(in_file["X"], bins=20, edgecolor='black', alpha=0.7)
sns.kdeplot(in_file["X"], fill=True, color='blue')
plt.xlabel("X")
plt.ylabel("Częstość")
plt.grid()

X = in_file["X"].to_numpy()
X_0 = in_file["X"][0:nX//2].to_numpy()
X_1 = in_file["X"][nX//2:nX].to_numpy()

Z_0 = np.sqrt(-2 * np.log(X_0)) * np.cos(2 * np.pi * X_1)
Z_1 = np.sqrt(-2 * np.log(X_0)) * np.sin(2 * np.pi * X_1)
Z = np.concatenate((Z_0, Z_1))

print("Z[1]:", Z[1], "Z[14]:", Z[14], "Z[38]:", Z[38])

sns.kdeplot(Z, fill=True, color='green', label='Z_1')

# plt.hist(Z_0, bins=20, edgecolor='black', alpha=0.7, label='Z_0')
# plt.hist(Z_1, bins=20, edgecolor='black', alpha=0.7, label='Z_1')

print("\n------------------------\n")
print("Rozkład Exp(5):")
print("dystrybuanta: F(x) = 1 - exp(-5 * x)")
print("odwrotność: F^(-1)(u) = -ln(1 - u) / 5 = -ln(u) / 5")

E = (-1.0 / 5.0) * np.log(X)

sns.kdeplot(E, fill=True, color='red', label='E')
print("E[1]:", E[1], "E[14]:", E[14], "E[38]:", E[38])

print("\n------------------------\n")

print("Rozkład f(x) = x na przedziale [0, 2]")
print("gęstość: f(x) = x / 2")
print("dystrybuanta: F(x) = x^2 / 4")
print("odwrotność: F^(-1)(u) = sqrt(4 * u)")
F = np.sqrt(4 * X)
sns.kdeplot(F, fill=True, color='orange', label='F')
print("F[1]:", F[1], "F[14]:", F[14], "F[38]:", F[38])

plt.show()


