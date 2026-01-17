# mlp_final_metrics.py
import pandas as pd
import numpy as np
from sklearn.neural_network import MLPClassifier
from sklearn.model_selection import StratifiedKFold
from sklearn.metrics import roc_auc_score, classification_report
from pathlib import Path

# 1. 读取 7 维 PCA 矩阵（已标准化）
file = Path('data/pca_1d.csv')
df = pd.read_csv(file)
X = df.drop(columns=['cardio'])
y = df['cardio']

# 2. 最佳参数（不调图）
best_model = MLPClassifier(
    activation='relu',
    alpha=0.001,
    early_stopping=True,
    hidden_layer_sizes=(256, 128, 64),
    learning_rate_init=0.0005,
    max_iter=1200,
    n_iter_no_change=15,
    random_state=42,
    solver='adam',
    validation_fraction=0.1
)

# 3. 5 折最终评估（只输出指标）
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

# 4. 详细指标（无图）
report = classification_report(y_test, y_pred, output_dict=True)
print('\n========== MLP_Best_Final ==========')
print(f"Accuracy : {np.mean(accs):.4f} ± {np.std(accs):.4f}")
print(f"Precision: {report['1']['precision']:.4f}")
print(f"Recall   : {report['1']['recall']:.4f}")
print(f"F1-score : {report['1']['f1-score']:.4f}")
print(f"AUC      : {np.mean(aucs):.4f} ± {np.std(aucs):.4f}")
