import pandas as pd 
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

input_file = 'l13z01.csv'
data = pd.read_csv(input_file, sep=',', header=None, names=['a', 'b', 'c', 'd'])

print(data.describe())

sns.kdeplot(data['a'], label='a', color='blue')
sns.kdeplot(data['b'], label='b', color='orange')
sns.kdeplot(data['c'], label='c', color='green')
sns.kdeplot(data['d'], label='d', color='red')
days = np.arange(1, len(data) + 1)
plt.legend()
plt.show()
