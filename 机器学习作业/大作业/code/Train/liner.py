# linear_baseline.py
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.linear_model import LogisticRegression
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.metrics import roc_curve, auc, classification_report
from sklearn.model_selection import StratifiedKFold
from pathlib import Path
import numpy as np



# 1. 读取已标准化数据（含标签）
file = Path(f'机器学习作业/大作业/data/heart_data_clean.csv')   # 你的已标准化文件
df = pd.read_csv(file)
X = df.drop(columns=['cardio'])
y = df['cardio']

# 2. 模型列表（线性类 2 个）
models = {
    'LogisticRegression': LogisticRegression(max_iter=1000, random_state=42),
    'LDA': LinearDiscriminantAnalysis()
}

# 3. 5 折分层交叉验证
cv = StratifiedKFold(n_splits=5, shuffle=True, random_state=42)
out_dir = Path('机器学习作业/大作业/image/linear_baseline/')
out_dir.mkdir(exist_ok=True)

for name, model in models.items():
    print(f'\n========== {name} ==========')
    aucs, accs, f1s, prec, rec = [], [], [], [], []

    for fold, (train_idx, test_idx) in enumerate(cv.split(X, y), 1):
        X_train, X_test = X.iloc[train_idx], X.iloc[test_idx]
        y_train, y_test = y.iloc[train_idx], y.iloc[test_idx]

        model.fit(X_train, y_train)
        y_pred = model.predict(X_test)
        y_prob = model.predict_proba(X_test)[:, 1]

        # 指标
        report = classification_report(y_test, y_pred, output_dict=True)
        accs.append(report['accuracy'])
        prec.append(report['1']['precision'])
        rec.append(report['1']['recall'])
        f1s.append(report['1']['f1-score'])

        # AUC
        fpr, tpr, _ = roc_curve(y_test, y_prob)
        aucs.append(auc(fpr, tpr))

    # 平均结果
    print(f"Accuracy: {np.mean(accs):.4f} ± {np.std(accs):.4f}")
    print(f"Precision: {np.mean(prec):.4f} ± {np.std(prec):.4f}")
    print(f"Recall: {np.mean(rec):.4f} ± {np.std(rec):.4f}")
    print(f"F1-score: {np.mean(f1s):.4f} ± {np.std(f1s):.4f}")
    print(f"AUC: {np.mean(aucs):.4f} ± {np.std(aucs):.4f}")

    # ROC 曲线（5 折平均）
    plt.figure(figsize=(5, 4))
    for fold, (train_idx, test_idx) in enumerate(cv.split(X, y), 1):
        X_train, X_test = X.iloc[train_idx], X.iloc[test_idx]
        y_train, y_test = y.iloc[train_idx], y.iloc[test_idx]
        model.fit(X_train, y_train)
        y_prob = model.predict_proba(X_test)[:, 1]
        fpr, tpr, _ = roc_curve(y_test, y_prob)
        plt.plot(fpr, tpr, lw=1, alpha=0.7, label=f'Fold {fold} AUC={auc(fpr, tpr):.3f}')
    plt.plot([0, 1], [0, 1], 'k--', lw=0.8)
    plt.xlabel('False Positive Rate')
    plt.ylabel('True Positive Rate')
    plt.title(f'{name}  5-Fold ROC')
    plt.legend()
    plt.tight_layout()
    plt.savefig(out_dir / f'roc_{name}.png', dpi=300)
    plt.close()

print('\n线性 baseline 完成')
