import numpy as np
import pandas as pd
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

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
r = 5e-8  # 半径
p_D = 0.944  # DMF密度
p_S = 1.260  # 环丁砜密度
p_C = 1.500  # 纤维素密度
k_B = 1.38e-23  # 玻尔兹曼常数
S_S = 1.0       # DMF对环丁砜饱和度
S_C = 0.15      # DMF对纤维素饱和度
n = 2e14        # 小液滴数量密度

t_evap = 100
dt = 1

# 定义模型
def model_evaporation(X, k1, k2, k3, k4, kh):
    T, H, SC = X
    results = []

    for i in range(len(T)):
        temp = T[i]
        humidity = H[i]
        sc = SC[i]

        # 初始质量
        m_D = 24.0
        m_S = 6.0
        m_C = sc * 0.3

        m_S_out = 0.01
        m_C_out = 0.01
        m_form = 0.01
        m_grow = 0.01
        integral = 0.02

        num_steps = int(t_evap / dt)
        time_points = np.linspace(0, t_evap, num_steps)

        for t in time_points:
            # 防止负质量
            m_D = max(m_D, 1e-6)
            m_S = max(m_S, 1e-6)
            m_C = max(m_C, 1e-6)

            # 计算phi_c
            total_vol = m_C / p_C + m_D / p_D + m_S / p_S + m_C_out / p_C
            if total_vol <= 0:
                phi_c = 1e-6
            else:
                phi_c = m_C_out / p_C / total_vol
                phi_c = np.clip(phi_c, 1e-6, 1e5)

            # 浓度
            V = m_S / p_S + m_D / p_D
            c = max((m_S + m_D) / max(V, 1e-6), 1e-6)

            # 饱和蒸汽压
            P_sat = 10 ** (6.09451 - 2725.96 / (temp + 273.15)) * 100000
            P_sat = max(P_sat, 1e-6)

            # DMF蒸发
            dm_D_dt = k1 * P_sat * c * max(1 - (humidity / 100) * kh, 1e-6)
            m_D -= dm_D_dt * dt

            # 粘度
            eta = max(1 + 2.5 * phi_c, 1e-6)

            # 扩散系数
            D = max((k_B * (temp + 273.15)) / (eta * r), 1e-12)
            v_avg = max(np.sqrt(D), 1e-6)

            # 析出质量
            m_S_out = max(m_S - m_D * S_S, 0)
            m_C_out = max(m_C - m_D * S_C, 0)

            # 更新质量
            m_S = max(m_S - m_S_out, 0)
            m_C = max(m_C - m_C_out, 0)

            # 碰撞频率
            Z = max(np.sqrt(n * r**2 * v_avg), 1e-6)

            # 形成质量
            dm_form_dt = max(k2 * Z, 0)
            m_form += dm_form_dt * dt

            # 小液滴浓度
            c_small = max(m_S_out / max(n * r**3, 1e-30), 1e-6)

            # 生长质量
            m_S_out_safe = max(m_S_out, 1e-6)
            dm_grow_dt = max(k3 * v_avg * c_small * (m_S_out_safe ** (2/3)), 0)
            m_grow += dm_grow_dt * dt

            integral += (dm_form_dt + dm_grow_dt) * dt

        P_p = max(k4 * integral, 0)
        results.append(P_p)

    return np.array(results)

# 数据准备
X_data = np.array([df["温度"], df["湿度"], df["固含量"]])
y_data = df["孔面积占比"].values

# 参数范围
param_bounds = ([1e-6, 1e-6, 1e-6, 1e-6, 0.001], [1, 1, 1, 1, 1])
p0 = [1e-4, 1e-4, 1e-4, 1e-4, 0.1]

# 拟合
popt, pcov = curve_fit(model_evaporation, X_data, y_data, p0=p0, bounds=param_bounds)
k1_fit, k2_fit, k3_fit, k4_fit, kh_fit = popt

# 预测
y_pred = model_evaporation(X_data, *popt)

# 评估
from sklearn.metrics import r2_score, mean_squared_error
r2 = r2_score(y_data, y_pred)
rmse = np.sqrt(mean_squared_error(y_data, y_pred))

print("拟合参数：")
print(f"k1 = {k1_fit:.6f}, k2 = {k2_fit:.6f}, k3 = {k3_fit:.6f}, k4 = {k4_fit:.6f}, kh = {kh_fit:.6f}")
print(f"R² = {r2:.4f}, RMSE = {rmse:.4f}")

# 可视化
plt.figure(figsize=(15, 5))
plt.subplot(1, 3, 1)
plt.scatter(df["温度"], y_data, label='实际值')
plt.scatter(df["温度"], y_pred, label='预测值')
plt.xlabel('温度')
plt.ylabel('孔面积占比')
plt.title('温度 vs 孔面积占比')
plt.legend()
plt.grid(True)

plt.subplot(1, 3, 2)
plt.scatter(df["湿度"], y_data, label='实际值')
plt.scatter(df["湿度"], y_pred, label='预测值')
plt.xlabel('湿度')
plt.ylabel('孔面积占比')
plt.title('湿度 vs 孔面积占比')
plt.legend()
plt.grid(True)

plt.subplot(1, 3, 3)
plt.scatter(df["固含量"], y_data, label='实际值')
plt.scatter(df["固含量"], y_pred, label='预测值')
plt.xlabel('固含量')
plt.ylabel('孔面积占比')
plt.title('固含量 vs 孔面积占比')
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()
