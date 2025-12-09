# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
import matplotlib.pyplot as plt
plt.rcParams['font.family'] = 'sans-serif'        # 无衬线
plt.rcParams['font.sans-serif'] = ['SimHei']      # Windows 黑体
# macOS / Linux 把 SimHei 换成 'DejaVu Sans' 或系统已有的中文名，例如
# plt.rcParams['font.sans-serif'] = ['PingFang SC']   # macOS 苹方
plt.rcParams['axes.unicode_minus'] = False        # 正常显示负号

# 1. 原始数据
x = np.array([10, 13, 22, 37, 45]).reshape(-1, 1)  # 必须二维
y = np.array([19, 60, 71, 74, 69])

# 2. 线性回归
model = LinearRegression()
model.fit(x, y)

a = model.intercept_   # 截距
b = model.coef_[0]     # 斜率

print(f"拟合方程: y = {a:.3f} + {b:.3f}*x")

# 3. 画图
plt.figure(figsize=(6, 4))
plt.scatter(x, y, color='b', label='Data')            # 散点
x_line = np.linspace(x.min(), x.max(), 100).reshape(-1, 1)
y_line = model.predict(x_line)
plt.plot(x_line, y_line, color='r', label='Linear fit')
plt.xlabel('广告费')
plt.ylabel('营销额')
plt.title('线性回归预测')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
