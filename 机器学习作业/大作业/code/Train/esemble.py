# ensemble_mlp_knn_xgb.py
import pandas as pd
import numpy as np
from sklearn.ensemble import VotingClassifier
from sklearn.neural_network import MLPClassifier
from sklearn.neighbors import KNeighborsClassifier
from xgboost import XGBClassifier
from sklearn.metrics import roc_auc_score, classification_report
from sklearn.model_selection import StratifiedKFold
from pathlib import Path

# 1. 读取 7 维 PCA 矩阵（已标准化）
file = Path('机器学习作业/大作业/data/heart_data_pca.csv')
df = pd.read_csv(file)
X = df.drop(columns=['cardio'])
y = df['cardio']

# 2. 复制你之前跑出的最佳参数（不调参）
base_models = [
    ('mlp', MLPClassifier(
        activation='relu',
        alpha=0.001,
        early_stopping=True,
        hidden_layer_sizes=(256, 128, 64),
        learning_rate_init=0.0005,
        max_iter=1200,
        n_iter_no_change=15,
        random_state=42,
        solver='adam',
        validation_fraction=0.1)),
    ('knn', KNeighborsClassifier(n_neighbors=5, weights='uniform')),
    ('xgb', XGBClassifier(n_estimators=100, max_depth=6, learning_rate=0.1, random_state=42))
]

# 3. 软投票（概率平均）
vote = VotingClassifier(estimators=base_models, voting='soft')
cv5 = StratifiedKFold(n_splits=5, shuffle=True, random_state=42)
aucs, accs = [], []

for train_idx, test_idx in cv5.split(X, y):
    X_train, X_test = X.iloc[train_idx], X.iloc[test_idx]
    y_train, y_test = y.iloc[train_idx], y.iloc[test_idx]

    vote.fit(X_train, y_train)
    y_pred = vote.predict(X_test)
    y_prob = vote.predict_proba(X_test)[:, 1]

    accs.append((y_pred == y_test).mean())
    aucs.append(roc_auc_score(y_test, y_prob))

report = classification_report(y_test, y_pred, output_dict=True)
print('\n========== MLP_KNN_XGB_Soft ==========')
print(f"Accuracy : {np.mean(accs):.4f} ± {np.std(accs):.4f}")
print(f"Precision: {report['1']['precision']:.4f}")
print(f"Recall   : {report['1']['recall']:.4f}")
print(f"F1-score : {report['1']['f1-score']:.4f}")
print(f"AUC      : {np.mean(aucs):.4f} ± {np.std(aucs):.4f}")

print('\nMLP+KNN+XGB 软投票完成！')
