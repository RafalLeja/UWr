import numpy as np

p = 1.0/3

n = 30
P_1 = 0
for i in range(8, 13):
    P_1 += (p**i) * ((1-p)**(n-i)) * (np.math.factorial(n) / (np.math.factorial(i) * np.math.factorial(n-i)))
print(f"P(8 <= X <= 12) = {P_1:.8f}")

n = 150
P_2 = 0
for i in range(40, 61):
    P_2 += (p**i) * ((1-p)**(n-i)) * (np.math.factorial(n) / (np.math.factorial(i) * np.math.factorial(n-i)))

print(f"P(40 <= X <= 60) = {P_2:.8f}")

n = 600
P_3 = 0
for i in range(160, 241):
    P_3 += (p**i) * ((1-p)**(n-i)) * (np.math.factorial(n) / (np.math.factorial(i) * np.math.factorial(n-i)))

print(f"P(160 <= X <= 240) = {P_3:.8f}")
