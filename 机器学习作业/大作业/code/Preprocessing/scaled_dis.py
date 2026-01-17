import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from pathlib import Path

df = pd.read_csv('机器学习作业/大作业/data/heart_data_scaled.csv')
out_dir = Path('机器学习作业/大作业/image')
out_dir.mkdir(exist_ok=True)

cols = [c for c in df.columns if c != 'cardio']
n_row = (len(cols) + 3 - 1) // 3
plt.figure(figsize=(18, 5 * n_row))

for i, col in enumerate(cols, 1):
    plt.subplot(n_row, 3, i)
    sns.histplot(data=df, x=col, hue='cardio', kde=True,
                 element='step', stat='density', common_norm=False,
                 palette={0: 'skyblue', 1: 'red'}, alpha=.6)
    plt.title(col)
    plt.grid(alpha=.3)

plt.tight_layout()
plt.savefig(out_dir / 'scaled_data_dist_split.png', dpi=300)
plt.close()

