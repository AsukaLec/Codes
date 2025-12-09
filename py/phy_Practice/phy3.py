import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
mpl.rcParams['font.family'] = 'SimHei'        # 正常显示中文
mpl.rcParams['axes.unicode_minus'] = False    # 正常显示负号

from scipy.signal import savgol_filter, find_peaks

# 原始数据
x = np.array([0, 20, 40, 60, 80, 100, 120, 140, 160, 180,
              200, 220, 240, 260, 280, 300, 320, 340, 360, 380,
              400, 420, 440, 460, 480, 500, 520, 540, 560, 580,
              600, 620, 640, 660, 680, 688])
y = np.array([45, 39, 35, 33, 33, 36, 41, 49, 58, 70,
              85, 100, 115, 129, 143, 155, 164, 170, 173, 173,
              171, 166, 162, 158, 158, 162, 176, 195, 227, 269,
              321, 383, 449, 522, 574, 596])

# 1. 平滑
y_smooth = savgol_filter(y, window_length=9, polyorder=3)

# 2. 找极值
# 极大值
peaks, _ = find_peaks(y_smooth)
x_max = x[peaks]
# 极小值（把信号取负）
troughs, _ = find_peaks(-y_smooth)
x_min = x[troughs]

print("极大值横坐标：", x_max)
print("极小值横坐标：", x_min)

# 3. 画图
plt.figure(figsize=(8, 5))
plt.plot(x, y, 'o', label='Original data')
plt.plot(x, y_smooth, '-', label='Smoothed curve')
plt.scatter(x_max, y_smooth[peaks], color='red', zorder=5, label='Maxima')
plt.scatter(x_min, y_smooth[troughs], color='blue', zorder=5, label='Minima')
plt.legend()
plt.xlabel('x')
plt.ylabel('y')
plt.title('Smoothed curve with extrema')
plt.grid(True)
plt.show()
