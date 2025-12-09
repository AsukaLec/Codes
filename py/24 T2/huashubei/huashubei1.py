import numpy as np
import pandas as pd
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt
from sklearn.metrics import r2_score, mean_squared_error
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False



# 原始实验数据
data = {
    '温度': [30, 30, 30, 30, 30, 30, 30, 30, 30, 40, 40, 40, 40, 40, 40, 40, 40, 40, 50, 50, 50, 50, 50, 50, 50, 50, 50],
    '湿度': [50, 50, 50, 70, 70, 70, 90, 90, 90, 50, 50, 50, 70, 70, 70, 90, 90, 90, 50, 50, 50, 70, 70, 70, 90, 90, 90],
    '固含量': [6, 6, 6, 8, 8, 8, 10, 10, 10, 8, 8, 8, 10, 10, 10, 6, 6, 6, 10, 10, 10, 6, 6, 6, 8, 8, 8],
    '孔面积占比': [18.09, 17.04, 19.45, 9.11, 9.4, 8.85, 9.35, 9.4, 9.08, 30.33, 31.2, 29.2, 24.12, 24.34, 23.11, 36.01, 35.35, 35.66, 6.41, 6.62, 6.73, 6.41, 6.62, 6.73, 8.38, 8.3, 8.29]
}

df = pd.DataFrame(data)

# 固定参数
m_S = 6.0  # g
r = 1.0    # 半径假设单位为1
t_evap = 100  # 模拟时间（单位时间）
dt = 1.0

# 原始模型函数
def model_raw(X, k2, k3, k4, a):
    T, H, SC = X
    result = []
    for i in range(len(T)):
        temp = T[i]
        hum = H[i]
        sc = SC[i]

        V = 24 + 6 + sc  # 简单加和体积
        c = m_S / V
        eta = 1 + a * sc
        v_avg = temp / eta

        M = 0.1  # 初始大液滴质量
        integral = 0
        for t in np.arange(0, t_evap, dt):
            dM = k2 * (m_S ** 2) * v_avg / (V ** 2 * r) + k3 * v_avg * c * (M ** (2/3))
            M += dM * dt

            integral += (k2 * (m_S ** 2) * v_avg / (V ** 2 * r) + k3 * v_avg * c * (M ** (2/3))) * dt

        alpha = k4 * integral
        result.append(alpha)
    return np.array(result)

# 准备拟合数据
X_data = np.array([df["温度"], df["湿度"], df["固含量"]])
y_data = df["孔面积占比"].values

# 拟合模型（初始猜测）
popt, pcov = curve_fit(model_raw, X_data, y_data, p0=[0.01, 0.01, 0.01, 0.01])
k2_fit, k3_fit, k4_fit, a_fit = popt

# 预测与评估
y_pred = model_raw(X_data, *popt)

# 计算性能指标
r2 = r2_score(y_data, y_pred)
rmse = np.sqrt(mean_squared_error(y_data, y_pred))

# 输出结果
print("原始模型拟合参数：")
print(f"k2 = {k2_fit:.4f}, k3 = {k3_fit:.4f}, k4 = {k4_fit:.4f}, a = {a_fit:.4f}")
print(f"R² = {r2:.4f}")
print(f"RMSE = {rmse:.4f}")

# 可视化
# 1. 实际值 vs 预测值
plt.figure(figsize=(10, 6))
plt.scatter(y_data, y_pred, c='blue', label='预测值')
plt.plot([min(y_data), max(y_data)], [min(y_data), max(y_data)], 'r--', label='理想值')
plt.xlabel('实际值')
plt.ylabel('预测值')
plt.title('实际值 vs 预测值')
plt.legend()
plt.show()

# 2. 残差图
residuals = y_data - y_pred
plt.figure(figsize=(10, 6))
plt.scatter(y_pred, residuals, c='blue')
plt.axhline(y=0, color='r', linestyle='--')
plt.xlabel('预测值')
plt.ylabel('残差')
plt.title('残差图')
plt.show()

# 3. 特征与目标值的关系图
features = ['温度', '湿度', '固含量']
plt.figure(figsize=(15, 5))
for i, feature in enumerate(features):
    plt.subplot(1, 3, i+1)
    plt.scatter(df[feature], y_data, c='blue', label='实际值')
    plt.scatter(df[feature], y_pred, c='orange', label='预测值', alpha=0.6)
    plt.xlabel(feature)
    plt.ylabel('孔面积占比')
    plt.title(f'{feature} vs 孔面积占比')
    plt.legend()
plt.tight_layout()
plt.show()
