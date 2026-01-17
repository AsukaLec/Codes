# bmi_vis.py
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from pathlib import Path

out_dir = Path('机器学习作业/大作业/data/visual/bmi_plots')
out_dir.mkdir(exist_ok=True)

df = pd.read_csv('机器学习作业/大作业/data/heart_data_clean.csv', usecols=['height', 'weight', 'cardio'])
df['bmi'] = df['weight'] / (df['height'] / 100) ** 2

# 1. 并排 KDE
plt.figure(figsize=(5, 3))
sns.kdeplot(data=df, x='bmi', hue='cardio', common_norm=False, fill=True)
plt.title('BMI vs cardio')
plt.savefig(out_dir / 'bmi_kde.png', dpi=300)
plt.close()

# 2. 每点 BMI 散点（y 轴随意）
plt.figure(figsize=(5, 5))
plt.scatter(df.query('cardio==0')['bmi'], [0]*len(df.query('cardio==0')),
            c='skyblue', s=1, alpha=.3, label='no cardio')
plt.scatter(df.query('cardio==1')['bmi'], [1]*len(df.query('cardio==1')),
            c='red', s=1, alpha=.8, label='cardio')
plt.yticks([0, 1], ['no cardio', 'cardio'])
plt.xlabel('BMI')
plt.title('BMI scatter by cardio')
plt.legend()
plt.tight_layout()
plt.savefig(out_dir / 'bmi_strip.png', dpi=300)
plt.show()
plt.close()

print('Saved → bmi_plots/')
