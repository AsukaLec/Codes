# pca_7d.py
import pandas as pd
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
from pathlib import Path
import seaborn as sns
import matplotlib.pyplot as plt

# 1. 读取清洗后原始特征
df = pd.read_csv('机器学习作业/大作业/data/heart_data_clean.csv')
X_orig = df.drop(columns=['cardio'])
y = df['cardio']

# 2. 标准化 + PCA 7维
X_scaled = StandardScaler().fit_transform(X_orig)
pca = PCA(n_components=7, random_state=42)
X_pca = pca.fit_transform(X_scaled)

# 3. 保存 7 维新特征
out_dir = Path('机器学习作业/大作业/data/analysis/PCA')
out_dir.mkdir(exist_ok=True)

pca_df = pd.DataFrame(X_pca, columns=[f'PC{i+1}' for i in range(7)])
pca_df['cardio'] = y.values
pca_df.to_csv(out_dir / 'X_pca_7d.csv', index=False)

# 4. 解释方差
print('Individual explained variance:', pca.explained_variance_ratio_)
print('Cumulative explained variance:', pca.explained_variance_ratio_.cumsum())

# 5. 可视化
plt.style.use('seaborn-v0_8-whitegrid')

# 5a 密度叠加图（2×4 网格，最后一张空）
fig, axes = plt.subplots(2, 4, figsize=(20, 10))
axes = axes.flatten()
for i, pc in enumerate([f'PC{j+1}' for j in range(7)]):
    sns.kdeplot(data=pca_df, x=pc, hue='cardio', common_norm=False,
                fill=True, palette={0: 'skyblue', 1: 'red'}, ax=axes[i])
    axes[i].set_title(pc)
    axes[i].grid(alpha=.3)
axes[7].set_visible(False)
plt.tight_layout()
plt.savefig(out_dir / 'pca_7d_dist.png', dpi=300)
plt.close()

# 5b 横向散点图（一张长图）
plt.figure(figsize=(16, 4))
sns.stripplot(data=pca_df.melt(id_vars='cardio', var_name='PC', value_name='value'),
              x='PC', y='value', hue='cardio', palette={0: 'skyblue', 1: 'red'},
              dodge=True, size=2, alpha=0.6)
plt.title('PCA-7D values vs cardio (strip)')
plt.grid(alpha=.3)
plt.tight_layout()
plt.savefig(out_dir / 'pca_7d_strip.png', dpi=300)
plt.close()

print('Saved → visual/pca_7d_dist.png & pca_7d_strip.png')
