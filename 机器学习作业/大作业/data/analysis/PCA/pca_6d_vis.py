# pca_6d_viz.py
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from pathlib import Path

# 1. 读 6 维 PCA 结果
pca_df = pd.read_csv('机器学习作业/大作业/data/analysis//PCA/X_pca_6d.csv')
y = pd.read_csv('机器学习作业/大作业/data/heart_data_clean.csv', usecols=['cardio'])
pca_df['cardio'] = y.values

out_dir = Path('机器学习作业/大作业/data/analysis/PCA')
out_dir.mkdir(exist_ok=True)

# 2. 密度叠加图（2×3 网格）
fig, axes = plt.subplots(2, 3, figsize=(18, 10))
axes = axes.flatten()
for i, pc in enumerate([f'PC{j+1}' for j in range(6)]):
    sns.kdeplot(data=pca_df, x=pc, hue='cardio', common_norm=False,
                fill=True, palette={0: 'skyblue', 1: 'red'}, ax=axes[i])
    axes[i].set_title(pc)
    axes[i].grid(alpha=.3)
plt.tight_layout()
plt.savefig(out_dir / 'pca_6d_dist.png', dpi=300)
plt.close()

# 3. 横向散点图（所有 PC 一张长图）
plt.figure(figsize=(15, 4))
sns.stripplot(data=pca_df.melt(id_vars='cardio', var_name='PC', value_name='value'),
              x='PC', y='value', hue='cardio', palette={0: 'skyblue', 1: 'red'},
              dodge=True, size=2, alpha=0.6)
plt.title('PCA-6D values vs cardio (strip)')
plt.grid(alpha=.3)
plt.tight_layout()
plt.savefig(out_dir / 'pca_6d_strip.png', dpi=300)
plt.close()

print('Saved → visual/pca_6d_dist.png & pca_6d_strip.png')
