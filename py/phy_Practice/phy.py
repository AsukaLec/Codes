import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import CubicSpline

# ---------- 1. 数据 ----------
xdat = np.array([787,887,987,1087,1187,1287,1337,1387,1437,1487,
                 1537,1587,1637,1687,1737,1787,1837,1887,1987,2087,
                 2187,2287,2387,2487], dtype=float)
ydat = np.array([27.96,34.6,42.9,54.4,71.1,97.7,118,146.4,188.1,250.8,
                 339,386,331,254.8,198.5,160.6,134.4,115.6,90.5,74.8,
                 63.9,56,50,45.2], dtype=float)

# ---------- 2. 建立三次样条 ----------
cs = CubicSpline(xdat, ydat, bc_type='not-a-knot')

# ---------- 3. 反解函数 ----------
def spline_inverse(y0, cs, x_min=None, x_max=None, N=1000):
    """
    求 cs(x) = y0 的所有实根，返回 ndarray（已排序）
    思路：先密集采样找符号变化区间，再用 Brent 求精根
    """
    if x_min is None: x_min = cs.x.min()
    if x_max is None: x_max = cs.x.max()
    x_dense = np.linspace(x_min, x_max, N)
    y_dense = cs(x_dense)
    roots = []
    for i in range(len(x_dense)-1):
        y1, y2 = y_dense[i], y_dense[i+1]
        if (y1 - y0) * (y2 - y0) <= 0:          # 符号变化 → 有根
            try:
                r = Brentq(lambda x: cs(x) - y0,
                           x_dense[i], x_dense[i+1])
                roots.append(r)
            except ValueError:
                pass
    return np.unique(np.round(roots, 6))

# ---------- 4. 画图 ----------
xx = np.linspace(xdat.min(), xdat.max(), 1000)
plt.figure(figsize=(6,4))
plt.plot(xdat, ydat, 'ko', label='raw data')
plt.plot(xx, cs(xx), 'r-', label='cubic spline')
plt.legend(); plt.show()

# ---------- 5. 示例 ----------
from scipy.optimize import brentq as Brentq

y0 = 272.94321753800734441872592377247
xs = spline_inverse(y0, cs)
print('y =', y0, '→  x =', xs)
