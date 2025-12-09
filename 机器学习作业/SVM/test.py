"""
SVM 决策边界示例
数据: 正例 (3,3) (5,3)   负例 (1,1)
输出: 决策直线方程  w0·x + w1·y + b = 0
"""

import numpy as np
from sklearn.svm import SVC

# 1. 构造数据
X = np.array([[3, 3],
              [5, 3],
              [1, 1],
              [6, 7],
              []])
y = np.array([1, 1, -1, 1])      # 1 为正例，-1 为负例

# 2. 训练线性 SVM（硬间隔即可，C 设很大）
model = SVC(kernel='linear', C=1e6)
model.fit(X, y)

# 3. 提取系数
w = model.coef_[0]            # 形状 (2,)
b = model.intercept_[0]

print('决策边界方程:')
print(f'{w[0]:.6f}·x + {w[1]:.6f}·y + {b:.6f} = 0')

# 4. 转成斜截式 y = kx + c （若 w1 ≠ 0）
if w[1] != 0:
    k = -w[0] / w[1]
    c = -b / w[1]
    print(f'斜截式:  y = {k:.6f}·x + {c:.6f}')
