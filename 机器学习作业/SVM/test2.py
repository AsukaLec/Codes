import numpy as np
import matplotlib.pyplot as plt
plt.rcParams['font.family'] = 'sans-serif'        # 无衬线
plt.rcParams['font.sans-serif'] = ['SimHei']      # Windows 黑体
# macOS / Linux 把 SimHei 换成 'DejaVu Sans' 或系统已有的中文名，例如
# plt.rcParams['font.sans-serif'] = ['PingFang SC']   # macOS 苹方
plt.rcParams['axes.unicode_minus'] = False        # 正常显示负号

# ---------- 数据 ----------
X = np.array([[3, 3], [5, 3], [1, 1]])
y = np.array([1, 1, -1])

# ---------- 两种支撑向量组合 ----------
cases = {
    # 'SV {1,3}': {'sv_idx': [0, 2], 'color': 'royalblue'},
    'SV {2,3}': {'sv_idx': [1, 2], 'color': 'orangered'}
}

plt.figure(figsize=(7,5))
plt.scatter(X[:,0], X[:,1], c=y, cmap='bwr', s=120, edgecolors='k', zorder=3)

for name, info in cases.items():
    sv_idx = info['sv_idx']
    sv_X, sv_y = X[sv_idx], y[sv_idx]

    # 解析解：w = λ1*y1*x1 + λ3*y3*x3  且 λ1=λ3（硬间隔+KKT）
    # 对 {1,3} 和 {2,3} 分别手算一次
    if name == 'SV {1,3}':
        # λ1=λ3=1/4, w=(0.5,0.5), b=-2
        w = np.array([0.5, 0.5]); b = -2
    else:  # {2,3}
        # λ2=λ3=1/10, w=(0.4,0.2), b=-1.6
        w = np.array([0.4, 0.2]); b = -1.6

    # 决策边界 w·x+b=0  →  x2 = -(w0*x0+b)/w1
    x0_plot = np.linspace(-1, 7, 200)
    x1_dec = -(w[0]*x0_plot + b) / w[1]
    plt.plot(x0_plot, x1_dec, '--', color=info['color'],
             label=f'{name} 决策边界')

    # 间隔边界  w·x+b=±1
    for sign, lw in [(1, 1), (-1, 1)]:
        x1_margin = -(w[0]*x0_plot + b - sign) / w[1]
        plt.plot(x0_plot, x1_margin, '-', color=info['color'],
                 alpha=0.5, lw=lw, label=f'{name} 间隔+{sign}' if sign==1 else None)

    # 支撑向量用粗边圈出
    plt.scatter(sv_X[:,0], sv_X[:,1], s=220, facecolors='none',
                edgecolors=info['color'], linewidths=2, zorder=4)

plt.xlim(-1, 7); plt.ylim(-1, 5)
plt.xlabel('$x_1$'); plt.ylabel('$x_2$')
plt.title('SVM')
plt.legend(); plt.grid(alpha=0.3)
plt.tight_layout()
plt.show()
