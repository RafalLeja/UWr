import pandas as pd 
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
from scipy import stats

input_file = 'l13z04.csv'
data = pd.read_csv(input_file, sep=',', header=None, names=['M', 'F'])

print(data.describe())

print("test t-welch")
t = (data['M'].mean() - data['F'].mean()) / \
    np.sqrt((data['M'].var() / len(data['M'])) + (data['F'].var() / len(data['F'])))
print("t-statistic:", t)
v = (data['M'].var() / len(data['M']) + data['F'].var() / len(data['F'])) ** 2 / \
    ((data['M'].var() / len(data['M'])) ** 2 / (len(data['M']) - 1) + \
    (data['F'].var() / len(data['F'])) ** 2 / (len(data['F']) - 1))
print("v:", v)
p_value = 1-stats.t.cdf(t, df=v)
print("p-value:", p_value)

statistic, p_value = stats.ttest_ind(data['M'], data['F'], equal_var=False)
print("t-test statistic:", statistic)
print("t-test p-value:", p_value)

sns.kdeplot(data = data['M'], label='M', color='blue')
sns.kdeplot(data = data['F'], label='F', color='red')

plt.title('Data Plot')
plt.xlabel('Index')
plt.legend()
plt.show()
