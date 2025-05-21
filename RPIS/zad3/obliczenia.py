import numpy as np

p = 1.0/3

n = 30
P_1 = 0
for i in range(8, 13):
    P_1 += (p**i) * ((1-p)**(n-i)) * (np.math.factorial(n) /
                                      (np.math.factorial(i) * np.math.factorial(n-i)))
print(f"P(8 <= X <= 12) = {P_1:.8f}")

n = 150
P_2 = 0
for i in range(40, 61):
    P_2 += (p**i) * ((1-p)**(n-i)) * (np.math.factorial(n) /
                                      (np.math.factorial(i) * np.math.factorial(n-i)))

print(f"P(40 <= X <= 60) = {P_2:.8f}")

n = 600
P_3 = 0
for i in range(160, 241):
    P_3 += (p**i) * ((1-p)**(n-i)) * (np.math.factorial(n) /
                                      (np.math.factorial(i) * np.math.factorial(n-i)))

print(f"P(160 <= X <= 240) = {P_3:.8f}")

e_1 = np.power(np.e, 0.3184)
n_1 = (1 - (1.0/3) + (1.0/3) * (1/e_1))

e_2 = np.power(np.e, -0.2876)
n_2 = (1 - (1.0/3) + (1.0/3) * (1/e_2))

pp_1 = np.power(e_1, 8) * np.power(n_1, 30) - \
    np.power(e_2, 12) * np.power(n_2, 30)
pp_2 = np.power(e_1, 40) * np.power(n_1, 150) - \
    np.power(e_2, 60) * np.power(n_2, 150)
pp_3 = np.power(e_1, 160) * np.power(n_1, 600) - \
    np.power(e_2, 240) * np.power(n_2, 600)
print(f"pp(8 <= X <= 12) = {pp_1:.8f}")
print(f"pp(40 <= X <= 60) = {pp_2:.8f}")
print(f"pp(160 <= X <= 240) = {pp_3:.8f}")
