import pandas as pd 
import numpy as np
from scipy import stats

in_file = pd.read_csv("l12z4.csv", sep=",", header=None, names=["X", "Y"])

EX = in_file["X"].mean()
EY = in_file["Y"].mean()
VX = in_file["X"].var()
VY = in_file["Y"].var()
nX = len(in_file["X"])
nY = len(in_file["Y"])

print("X:")
print("Średnia = ", EX)
print("Wariancja = ", VX)
print("Odchylenie standardowe = ", in_file["X"].std())
print
print("Y:")
print("Średnia = ", EY)
print("Wariancja = ", VX)
print("Odchylenie standardowe = ", in_file["Y"].std())
print("\n-----------------------\n")

print("Zadanie 4 - test Z:")
Z4 = (EX - EY) / np.sqrt(VX / nX + VX / nY)
print("Z = ", Z4)
H4 = 1 - stats.norm.cdf(Z4)
print("Hipoteza 4: 1 - F(Z) = ", H4)

print("\n-----------------------\n")

print("Zadanie 5:")
print("test t-Studenta:")
t5 = ((EX - EY) * np.sqrt(nX + nY- 2)) \
/ np.sqrt((nX * VX + nY * VX) * ((1.0/nX) + (1.0/nY))) 
print("t = ", t5)
H5 = 1 - stats.t.cdf(t5, df=nX + nY - 2)
print("Hipoteza 5.1: 1 - F(t) = ", H5)
print()
print("test welcha:")
t_welch = ((EX - EY) * np.sqrt(nX * nY)) \
/ np.sqrt((nX * VX + nY * VX) * ((1.0/nX) + (1.0/nY)))
print("t_welch = ", t_welch)
r = np.power((VX / nX + VY / nY), 2)/ \
    ((VX / nX) ** 2) * ((nX - 1)/(nX**2)) + \
    ((VY / nY) ** 2) * ((nY - 1)/(nY**2)) 
print("r = ", r)
H5_welch = 1 - stats.t.cdf(t_welch, df= r)
print("Hipoteza 5.2: 1 - F(t_welch) = ", H5_welch)
print("\n-----------------------\n")


print("Zadanie 6:")
print("test F-Snedecora")

F6 = VX / VY
print("F = ", F6)
H6 = 1 - stats.f.cdf(F6, dfn=nX, dfd=nY)
print("Hipoteza 6: 1 - F(F) = ", H6)

print("\n-----------------------\n")

print("Zadanie 7:")
print(f"to samo ale F({nX},{nY}) = {1 - stats.f.cdf(F6, dfn=nX-1, dfd=nY-1)}")
