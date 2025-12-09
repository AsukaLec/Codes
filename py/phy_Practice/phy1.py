import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import CubicSpline

# ---- 1. 数据 ----
xdat = np.array([787,887,987,1087,1187,1287,1337,1387,1437,1487,
                 1537,1587,1637,1687,1737,1787,1837,1887,1987,2087,
                 2187,2287,2387,2487])
ydat = np.array([27.96,34.6,42.9,54.4,71.1,97.7,118,146.4,188.1,250.8,
                 339,386,331,254.8,198.5,160.6,134.4,115.6,90.5,74.8,
                 63.9,56,50,45.2])
# ---- 2. 拟合（这里用 6 次，可自行改阶数） ----
deg = 6
coef = np.polyfit(xdat, ydat, deg)   # 从高次到低次的系数
poly = np.poly1d(coef)               # 可调用对象

# ---- 3. 反解 ----
def poly_inverse(y0, poly, x_min=xdat.min(), x_max=xdat.max()):
    """
    解 poly(x) = y0 的全部实根，返回 ndarray；区间外根置 nan
    """
    coeffs = poly.coeffs.copy()
    coeffs[-1] -= y0          # 常数项减去 y0
    all_roots = np.roots(coeffs)
    real_roots = []
    for r in all_roots:
        if np.isreal(r):
            x = r.real
            if x_min <= x <= x_max:
                real_roots.append(x)
    return np.unique(np.round(real_roots, 6))

# ---- 4. 画图 ----
xx = np.linspace(xdat.min(), xdat.max(), 1000)
plt.figure(figsize=(6,4))
plt.plot(xdat, ydat, 'ko', label='raw')
plt.plot(xx, poly(xx), 'g-', label=f'poly deg={deg}')
plt.legend(); plt.show()

# ---- 5. 示例反解 ----
y0 = 100
print('y =', y0, '对应 x =', poly_inverse(y0, poly))
