# lgb_quick_metrics.py
import pandas as pd
import numpy as np
from lightgbm import LGBMClassifier
from sklearn.model_selection import StratifiedKFold
from sklearn.metrics import roc_auc_score, classification_report
from pathlib import Path

# 1. 读取 7 维 PCA 矩阵（已标准化）
file = Path('机器学习作业/大作业/data/heart_data.csv')
df = pd.read_csv(file)
X = df.drop(columns=['cardio'])
y = df['cardio']

# 2. LightGBM 轻量参数（秒训练）
model = LGBMClassifier(
    n_estimators=100,
    max_depth=6,
    learning_rate=0.1,
    random_state=42,
    n_jobs=-1
)

# 3. 5 折交叉验证（不画图、不 verbose）
cv5 = StratifiedKFold(n_splits=5, shuffle=True, random_state=10)
aucs, accs = [], []

for train_idx, test_idx in cv5.split(X, y):
    X_train, X_test = X.iloc[train_idx], X.iloc[test_idx]
    y_train, y_test = y.iloc[train_idx], y.iloc[test_idx]

    model.fit(X_train, y_train)   # 关闭 LGB 日志
    y_pred = model.predict(X_test)
    y_prob = model.predict_proba(X_test)[:, 1]

    accs.append((y_pred == y_test).mean())
    aucs.append(roc_auc_score(y_test, y_prob))

# 4. 详细指标（无图）
report = classification_report(y_test, y_pred, output_dict=True)
print('\n========== LightGBM_7d ==========')
print(f"Accuracy : {np.mean(accs):.4f} ± {np.std(accs):.4f}")
print(f"Precision: {report['1']['precision']:.4f}")
print(f"Recall   : {report['1']['recall']:.4f}")
print(f"F1-score : {report['1']['f1-score']:.4f}")
print(f"AUC      : {np.mean(aucs):.4f} ± {np.std(aucs):.4f}")

print('\nLightGBM（无图快版）完成！')
