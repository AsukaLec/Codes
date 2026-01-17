# pca_tune_pure.py
import pandas as pd
from sklearn.decomposition import PCA
from pathlib import Path

n_components = 8               


df = pd.read_csv('机器学习作业/大作业/data/heart_data_scaled.csv')
X = df.drop(columns=['cardio'])   
y = df['cardio']                  


pca = PCA(n_components=n_components, random_state=42)
X_pca = pca.fit_transform(X)


out_dir = Path('机器学习作业/大作业/data/')
out_dir.mkdir(exist_ok=True)
pca_df = pd.DataFrame(X_pca, columns=[f'PC{i+1}' for i in range(n_components)])
pca_df['cardio'] = y.values          
pca_df.to_csv(out_dir / f'X_pca_{n_components}d_pure.csv', index=False)

# 解释方差
ind = pca.explained_variance_ratio_
cum = ind.cumsum()
print(f'{n_components}D PCA 完成！')
print('Individual explained variance:', ind)
print('Cumulative explained variance:', cum)
