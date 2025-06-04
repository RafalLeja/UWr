import pandas as pd 
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
from scipy import stats

input_file = 'l13z01.csv'
data = pd.read_csv(input_file, sep=',', header=None, names=['a', 'b', 'c', 'd'])

print(data.describe())

stat, p_value = stats.kruskal(data['a'], data['b'], data['c'], data['d'])
print(f"Kruskal-Wallis test statistic: {stat}, p-value: {p_value}")

flattened = data.values.flatten()
ranks = stats.rankdata(flattened)  # Nadajemy rangi globalnie

# Przekształcamy rangi z powrotem do oryginalnego kształtu (4 kolumny)
ranked_data = ranks.reshape(data.shape)

# Liczymy sumę rang dla każdej kolumny
R = ranked_data.sum(axis=0)  # R[0] dla kolumny 'a', itd.

# Liczba grup i liczność w każdej
k = data.shape[1]           # 4 grupy
n_i = data.shape[0]         # 20 próbek w każdej
N = k * n_i                 # 80

# Obliczamy statystykę H według wzoru:
H = (12 / (N * (N + 1))) * np.sum((R**2) / n_i) - 3 * (N + 1)

print(f"Wartość statystyki Kruskala-Wallisa: {H:.4f}")
dyst = 1- stats.distributions.chi2.cdf(H, k - 1)
print(f"Wartość krytyczna dla rozkładu chi-kwadrat: {dyst:.4f}")


sns.kdeplot(data['a'], label='a', color='blue')
sns.kdeplot(data['b'], label='b', color='orange')
sns.kdeplot(data['c'], label='c', color='green')
sns.kdeplot(data['d'], label='d', color='red')
days = np.arange(1, len(data) + 1)
plt.legend()
plt.show()
