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
print("Hipoteza 1 - F(Z) = ", H4)

print("\n-----------------------\n")

print("Zadanie 5:")
print("test t-Studenta:")
t5 = ((EX - EY) * np.sqrt(nX * nY- 2)) \
/ np.sqrt((nX * VX + nY * VX) * ((1.0/nX) + (1.0/nY))) 
print("t = ", t5)
H5 = 1 - stats.t.cdf(t5, df=nX + nY - 2)
print("Hipoteza 2 - F(t) = ", H5)
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
print("Hipoteza 2 - F(t_welch) = ", H5_welch)
print("\n-----------------------\n")