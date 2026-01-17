# linear_svc_fast.py
import pandas as pd
import numpy as np
from sklearn.svm import LinearSVC
from sklearn.metrics import roc_auc_score, classification_report
from sklearn.model_selection import StratifiedKFold
from pathlib import Path

# 1. 读取 7 维 PCA 矩阵（已标准化）
file = Path('机器学习作业/大作业/data/heart_data_pca.csv')
df = pd.read_csv(file)
X = df.drop(columns=['cardio'])
y = df['cardio']

# 2. 线性 SVC（轻量参数，秒训练）
model = LinearSVC(C=0.1, max_iter=1000, random_state=42)

# 3. 5 折交叉验证（不画图）
cv = StratifiedKFold(n_splits=5, shuffle=True, random_state=42)

print('\n========== LinearSVC_7d ==========')
aucs, accs, f1s, prec, rec = [], [], [], [], []

for train_idx, test_idx in cv.split(X, y):
    X_train, X_test = X.iloc[train_idx], X.iloc[test_idx]
    y_train, y_test = y.iloc[train_idx], y.iloc[test_idx]

    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)
    y_score = model.decision_function(X_test)  # 决策值用于 AUC

    # 指标
    report = classification_report(y_test, y_pred, output_dict=True)
    accs.append(report['accuracy'])
    prec.append(report['1']['precision'])
    rec.append(report['1']['recall'])
    f1s.append(report['1']['f1-score'])
    aucs.append(roc_auc_score(y_test, y_score))

# 4. 平均结果
print(f"Accuracy : {np.mean(accs):.4f} ± {np.std(accs):.4f}")
print(f"Precision: {np.mean(prec):.4f} ± {np.std(prec):.4f}")
print(f"Recall   : {np.mean(rec):.4f} ± {np.std(rec):.4f}")
print(f"F1-score : {np.mean(f1s):.4f} ± {np.std(f1s):.4f}")
print(f"AUC      : {np.mean(aucs):.4f} ± {np.std(aucs):.4f}")

print('\nLinearSVC（无图快版）完成！')
