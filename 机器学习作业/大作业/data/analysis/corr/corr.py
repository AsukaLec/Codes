import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from pathlib import Path

df = pd.read_csv('机器学习作业/大作业/data/heart_data_clean.csv')
corr = df.corr()

plt.figure(figsize=(10, 8))
sns.heatmap(corr, annot=True, fmt='.2f', cmap='coolwarm', square=True)
plt.title('Pearson Correlation Matrix')
plt.tight_layout()
plt.savefig('机器学习作业/大作业/data/correlation_heatmap.png', dpi=300)
plt.close()
print('Correlation heatmap saved → discrete_plots/correlation_heatmap.png')
