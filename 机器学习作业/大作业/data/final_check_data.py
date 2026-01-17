# check_norm_scatter.py
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('机器学习作业/大作业/data/heart_data_clean.csv')
cols = ['age', 'height', 'weight', 'ap_hi', 'ap_lo']

plt.figure(figsize=(15, 3))
for i, col in enumerate(cols, 1):
    plt.subplot(1, 5, i)
    plt.scatter(df[col], [0]*len(df), s=1, alpha=0.3, color='skyblue')
    plt.title(col)
    plt.grid(alpha=0.3)
    plt.yticks([])         

plt.tight_layout()
plt.show()
