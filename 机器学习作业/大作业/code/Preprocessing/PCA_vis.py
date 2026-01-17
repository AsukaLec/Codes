# pca_visual_n.py
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from pathlib import Path


n = 10    

# 1. 读 n 维 PCA 结果
pca_df = pd.read_csv(f'data/pca_{n}d.csv')
y = pd.read_csv('data/heart_data_clean.csv', usecols=['cardio'])
pca_df['cardio'] = y.values

out_dir = Path('image')
out_dir.mkdir(exist_ok=True)

# 2. 密度图：自动 2×ceil(n/3) 网格
n_row = (n + 2) // 3
fig, axes = plt.subplots(n_row, 3, figsize=(4 * 3, 4 * n_row))
axes = axes.flatten()
for i, pc in enumerate([f'PC{j+1}' for j in range(n)]):
    sns.kdeplot(data=pca_df, x=pc, hue='cardio', common_norm=False,
                fill=True, palette={0: 'skyblue', 1: 'red'}, ax=axes[i])
    axes[i].set_title(pc)
    axes[i].grid(alpha=.3)
# 隐藏多余子图
for j in range(n, len(axes)):
    axes[j].set_visible(False)
plt.tight_layout()
plt.savefig(out_dir / f'pca_{n}d_dist.png', dpi=300)
plt.close()


# 3. 横向散点图（所有 PC 一张长图）
plt.figure(figsize=(3 * n, 4))
sns.stripplot(data=pca_df.melt(id_vars='cardio', var_name='PC', value_name='value'),
              x='PC', y='value', hue='cardio', palette={0: 'skyblue', 1: 'red'},
              dodge=True, size=2, alpha=0.6)
plt.title(f'PCA-{n}D values vs cardio (strip)')
plt.grid(alpha=.3)
plt.tight_layout()
plt.savefig(out_dir / f'pca_{n}d_strip.png', dpi=300)
plt.close()