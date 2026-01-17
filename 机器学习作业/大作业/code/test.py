# pca_importance_trim.py
import pandas as pd
import numpy as np
from sklearn.decomposition import PCA
from sklearn.ensemble import RandomForestClassifier
from sklearn.inspection import permutation_importance
from sklearn.model_selection import cross_val_score
from pathlib import Path

# ========== 接口：可调 ==========
n_components = 12          # 先让 PCA 升到较高维
# ================================

# 1. 读取已标准化数据（含标签）
file = Path('机器学习作业/大作业/data/heart_data_scaled.csv')
df = pd.read_csv(file)
X_raw = df.drop(columns=['cardio'])
y = df['cardio'].values

# 2. PCA 升到 n_components 维
pca = PCA(n_components=n_components, random_state=42)
X_pca = pca.fit_transform(X_raw)

# 3. 排列重要性（用 RF 快速估）
rf = RandomForestClassifier(n_estimators=300, max_depth=6, random_state=42)
rf = RandomForestClassifier(n_estimators=300, max_depth=6, random_state=42)
rf.fit(X_pca, y)                                    # ← 补上这一行
imp = permutation_importance(rf, X_pca, y, n_repeats=10, random_state=42)
imp_df = pd.DataFrame({'PC': [f'PC{i+1}' for i in range(n_components)],
                       'importance': imp.importances_mean}).sort_values('importance', ascending=False)

# 4. 从 Top-1 逐步回退，找 AUC 不跌的最小 k
auc_full = cross_val_score(rf, X_pca, y, cv=5, scoring='roc_auc').mean()
print(f'全维 {n_components}D AUC = {auc_full:.4f}')

best_k, best_auc = n_components, auc_full
for k in range(1, n_components):
    X_top = X_pca[:, imp_df.head(k).index]
    auc_k = cross_val_score(rf, X_top, y, cv=5, scoring='roc_auc').mean()
    if auc_k >= auc_full - 0.001:          # 容忍 0.1% 掉点
        best_k, best_auc = k, auc_k
        break

print(f'最佳维度 = {best_k}  （AUC={best_auc:.4f}）')

# 5. 保存最佳 PC 矩阵
X_best = X_pca[:, imp_df.head(best_k).index]
out_df = pd.DataFrame(X_best, columns=[f'PC{i+1}' for i in range(best_k)])
out_df['cardio'] = y
out_df.to_csv(Path('data/') / f'X_pca_{best_k}d_trim.csv', index=False)

print(f'已保存最佳 PC 矩阵 → X_pca_{best_k}d_trim.csv')
