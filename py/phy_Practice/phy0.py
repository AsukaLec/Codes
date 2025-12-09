import numpy as np
import matplotlib.pyplot as plt
plt.rcParams['font.sans-serif'] = ['SimHei']   # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False     # 用来正常显示负号

# 原始数据
Is = np.array([0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9])
UH = np.array([12.32, 24.6375, 36.4725, 48.5175, 59.8475, 70.9, 81.055, 91.1125,
               100.6425, 109.5075, 117.79, 125.8975, 133.035, 139.83, 145.94,
               151.8175, 157.19, 162.3725])

# 线性拟合：1次多项式，返回 [斜率, 截距]
k, b = np.polyfit(Is, UH, 1)
print(f"斜率  k = {k:.6f}")   # 单位：mV/mA
print(f"截距  b = {b:.6f}")   # 理想霍尔元件应接近 0

# 绘图
plt.figure(figsize=(6, 4))
plt.plot(Is, UH, 'o', label='实验数据')
plt.plot(Is, k*Is + b, 'r-', label=f'线性拟合: UH = {k:.3f}·Is')
plt.xlabel('Is / mA')
plt.ylabel('UH / mV')
plt.title('霍尔电压 vs 工作电流')
plt.legend()
plt.grid(True)
plt.show()
