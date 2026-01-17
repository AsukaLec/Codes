# pca_6d.py
import pandas as pd
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
from pathlib import Path

# 1. 读取清洗后数据
df = pd.read_csv('机器学习作业/大作业/data/heart_data_clean.csv')
X = df.drop(columns=['cardio'])

# 2. 标准化 + PCA 6维
X_scaled = StandardScaler().fit_transform(X)
pca = PCA(n_components=6, random_state=42)
X_pca = pca.fit_transform(X_scaled)

# 3. 保存 6 维新特征
out_dir = Path('机器学习作业/大作业/data/analysis/PCA')
out_dir.mkdir(exist_ok=True)

new_X = pd.DataFrame(X_pca, columns=[f'PC{i+1}' for i in range(6)])
new_X.to_csv(out_dir / 'X_pca_6d.csv', index=False)

# 4. 解释方差
print('Individual explained variance:', pca.explained_variance_ratio_)
print('Cumulative explained variance:', pca.explained_variance_ratio_.cumsum())

# 5. 载荷表
(pd.DataFrame(pca.components_.T, columns=new_X.columns, index=X.columns)
   .to_csv(out_dir / 'pca_6d_loading.csv'))

print('6-D PCA done! → visual/X_pca_6d.csv')
