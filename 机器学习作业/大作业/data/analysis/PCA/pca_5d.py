# pca_5d.py
import pandas as pd
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
from pathlib import Path

df = pd.read_csv('机器学习作业/大作业/data/heart_data_clean.csv')
X_scaled = StandardScaler().fit_transform(df.drop(columns=['cardio']))

pca = PCA(n_components=5, random_state=42)
X_pca = pca.fit_transform(X_scaled)

out_dir = Path('机器学习作业/大作业/data/analysis/PCA')
out_dir.mkdir(exist_ok=True)

# 保存 5 维新特征
new_X = pd.DataFrame(X_pca, columns=[f'PC{i+1}' for i in range(5)])
new_X.to_csv(out_dir / 'X_pca_5d.csv', index=False)

# 打印累计解释方差
print('Individual explained variance:', pca.explained_variance_ratio_)
print('Cumulative explained variance:', pca.explained_variance_ratio_.cumsum())

# 可选：载荷表
(pd.DataFrame(pca.components_.T, columns=new_X.columns, index=df.drop(columns=['cardio']).columns)
   .to_csv(out_dir / 'pca_5d_loading.csv'))

print('5-D PCA features saved → visual/X_pca_5d.csv')
