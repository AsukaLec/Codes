# lda_only.py
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis as LDA
from sklearn.preprocessing import StandardScaler
from pathlib import Path

# 1. 读取清洗后数据
df = pd.read_csv('机器学习作业/大作业/data/heart_data_clean.csv')
X, y = df.drop(columns=['cardio']), df['cardio']
X_scaled = StandardScaler().fit_transform(X)

# 2. LDA 降 1D
lda = LDA(n_components=1)
X_lda = lda.fit_transform(X_scaled, y).ravel()

# 3. 可视化
out_dir = Path('机器学习作业/大作业/data/analysis')
out_dir.mkdir(exist_ok=True)

plt.figure(figsize=(6, 5))
for cls, color, lbl in zip([0, 1], ['skyblue', 'red'], ['no cardio', 'cardio']):
    mask = y == cls
    plt.scatter(X_lda[mask], [0] * mask.sum(),   # ← 用 mask.sum() 即长度
                c=color, s=15, alpha=.7, label=lbl)
plt.title('LDA-1D'); plt.legend(); plt.grid(alpha=.3)
plt.ylim(-.5, .5)
plt.tight_layout()
plt.savefig(out_dir / 'lda_1d.png', dpi=300)
plt.close()

# 4. 载荷表
pd.DataFrame(lda.coef_.T, columns=['LD1'], index=X.columns)\
  .to_csv(out_dir / 'lda_loading.csv')

print('LDA done! → visual/lda_1d.png + lda_loading.csv')
