# mlp_increment.py
import pandas as pd
import numpy as np
from sklearn.neural_network import MLPClassifier
from sklearn.model_selection import GridSearchCV, StratifiedKFold
from sklearn.metrics import roc_auc_score, classification_report
from pathlib import Path

# 1. 读取 7 维 PCA 矩阵（已标准化）
file = Path('机器学习作业/大作业/data/heart_data_pca.csv')
df = pd.read_csv(file)
X = df.drop(columns=['cardio'])
y = df['cardio']

# ========== 接口：每步只改这里 ==========
# ① 层深 + 宽度
param = {
    'hidden_layer_sizes': [(128, 64), (256, 128, 64), (512, 256, 128)],
    'activation': ['relu', 'tanh'],
    'solver': ['adam'],
    'alpha': [1e-4, 1e-3],
    'learning_rate_init': [1e-3, 5e-4],
    'max_iter': [1200],
    'early_stopping': [True],
    'validation_fraction': [0.1],
    'n_iter_no_change': [15],
    'random_state': [42]
}
# =====================================

# 2. 3 折快筛 + AUC 评分（无图，不 verbose）
mlp = MLPClassifier()
grid = GridSearchCV(mlp, param, cv=3, scoring='roc_auc', n_jobs=-1, verbose=0)
grid.fit(X, y)

print("最佳参数:", grid.best_params_)
print("最佳 3 折 AUC:", grid.best_score_)

# 3. 用最佳参数跑 5 折最终评估（只输出指标）
best_model = grid.best_estimator_
cv5 = StratifiedKFold(n_splits=5, shuffle=True, random_state=42)
aucs, accs = [], []

for train_idx, test_idx in cv5.split(X, y):
    X_train, X_test = X.iloc[train_idx], X.iloc[test_idx]
    y_train, y_test = y.iloc[train_idx], y.iloc[test_idx]

    best_model.fit(X_train, y_train)
    y_pred = best_model.predict(X_test)
    y_prob = best_model.predict_proba(X_test)[:, 1]

    accs.append((y_pred == y_test).mean())
    aucs.append(roc_auc_score(y_test, y_prob))

print(f"5 折最终 Accuracy: {np.mean(accs):.4f} ± {np.std(accs):.4f}")
print(f"5 折最终 AUC: {np.mean(aucs):.4f} ± {np.std(aucs):.4f}")

print('\nMLP 增量调参（无图）完成！')
