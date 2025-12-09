import numpy as np
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.pyplot as plt
plt.rcParams['font.family'] = 'sans-serif'        # 无衬线
plt.rcParams['font.sans-serif'] = ['SimHei']      # Windows 黑体
# macOS / Linux 把 SimHei 换成 'DejaVu Sans' 或系统已有的中文名，例如
# plt.rcParams['font.sans-serif'] = ['PingFang SC']   # macOS 苹方
plt.rcParams['axes.unicode_minus'] = False        # 正常显示负号

# ===== 1. 最新数据 =====
t = np.array([100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40])
Ig = np.array([100, 98, 95, 91, 86.5, 82, 76, 70, 62.5, 57, 49, 41, 34])
invT = np.array([0.002679887, 0.002716284, 0.002753683, 0.002792126,
                 0.002831658, 0.002872325, 0.002914177, 0.002957267,
                 0.003001651, 0.003047387, 0.003094538, 0.003143171, 0.003193358])
Rt = np.array([304.0767574, 344.958959, 408.1058164, 495.8922368,
               599.9103294, 709.9626468, 867.0296978, 1037.264108,
               1271.235677, 1459.953996, 1764.79294, 2112.363, 2459.064401])
LnRt = np.array([5.717280161, 5.843425451, 6.011526495, 6.206358639,
                 6.396780193, 6.565212359, 6.76507323, 6.944341861,
                 7.14774468, 7.286160205, 7.475788648, 7.655562505, 7.807536232])

# ===== 2. 图 1：Rt ~ t =====
plt.figure(1)
plt.plot(t, Rt, 'o-', label='Rt vs t')
plt.xlabel('t / °C')
plt.ylabel('Rt / Ω')
plt.title('图 1：Rt 随温度 t 的变化')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()

# ===== 3. 图 2：LnRt ~ 1/T 并线性拟合 =====
plt.figure(2)
plt.scatter(invT, LnRt, label='data')

# 线性拟合
slope, intercept = np.polyfit(invT, LnRt, 1)
fit_line = slope * invT + intercept
plt.plot(invT, fit_line, 'r-', label=f'fit: y={slope:.2f}x+{intercept:.3f}')

# R²
r2 = 1 - np.sum((LnRt - fit_line)**2) / np.sum((LnRt - LnRt.mean())**2)

plt.xlabel('1/T / K⁻¹')
plt.ylabel('Ln Rt')
plt.title('图 2：LnRt 随 1/T 的变化及线性拟合')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()

# ===== 4. 输出拟合结果 =====
print('拟合结果（LnRt = slope*(1/T) + intercept）')
print(f'斜率  slope   = {slope:.4f}  K')
print(f'截距  intercept = {intercept:.4f}')
print(f'R²    = {r2:.5f}')
