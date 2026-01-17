# all_cols_dist_split.py
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from pathlib import Path

df = pd.read_csv('机器学习作业/大作业/data/data_scaled.csv')
out_dir = Path('机器学习作业/大作业/data')
out_dir.mkdir(exist_ok=True)

plt.figure(figsize=(22, 20))
for i, col in enumerate(df.columns):
    plt.subplot(4, 3, i + 1)

    sns.histplot(data=df, x=col, hue='cardio', kde=True,
                 element='step', stat='density', common_norm=False,
                 palette={0: 'skyblue', 1: 'red'}, alpha=.6)
    plt.title(col)
    plt.grid(alpha=.3)

plt.tight_layout()
plt.savefig(out_dir / 'all_columns_dist_split.png', dpi=300)
plt.close()
print('Saved → visual/discrete_plots/all_columns_dist_split.png')
