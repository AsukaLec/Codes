
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
r = 5 * 1e-8    # 半径

p_D = 0.944 #DMF密度
p_S = 1.260 #环丁砜密度
p_C = 1.500 #纤维素的密度

k_B = 1.38e-23 # 玻尔兹曼常数

S_S = 0.25     # dmf 对 环丁砜 饱和度 (估计值)
S_C = 0.15    # dmf 对 纤维素 饱和度 (估计值)

n = 2 * 1e14       # 分子数量 (估计值)

# 模拟时间设置
t_evap = 1  
dt = 1      

# 定义模拟蒸发过程的函数
def model_evaporation(X, k1, k2, k3, k4, kh):
    T, H, SC = X
    results = []

    for i in range(len(T)):
        temp = T[i]
        humidity = H[i]
        sc = SC[i]
        
        # 初始化变量
        m_D = 24  # 初始液滴质量
        m_S = 6  # g
        m_C = sc * 0.3      # 恒量质量 (假设值)

        m_S_out = 0.01
        m_C_out = 0.01

        m_form = 0.01
        m_grow = 0.01

        integral = 0.02

        # 时间步长
        num_steps = int(t_evap / dt)
        time_points = np.linspace(0, t_evap, num_steps)

        for t in time_points:

            phi_c = (m_C_out / p_C) / (m_C / p_C + m_D / p_D + m_S / p_S + m_C_out / p_C)    # 固体粒子体积分数
            
            # 计算浓度
            V = m_S/p_S + m_D/p_D
            c = (m_S + m_D) / V

            # 计算饱和蒸汽压 
            P_sat = 10 ** (6.09451 - 2725.96 / (temp + 28.209 + 273.15)) 
            P_sat = P_sat * 1820
            
            # 更新液滴质量
            dm_D_dt =  abs(k1 * P_sat * c * (1 - (humidity  * kh ) / 100) )
            m_D -= dm_D_dt * dt
            m_D = max(m_D, 1e-8)

            # 计算粘度
            eta = 1 + 2.5 * phi_c

            # 计算扩散系数
            D = (k_B * temp) / (eta * r )    

            # 计算平均速度
            v_avg = np.sqrt(D)


            # 计算 Z
            Z = np.sqrt(n * r**2 * v_avg)

            # 更新输出质量
            m_S_out = max(m_S - m_D * S_S, 0)
            m_S -= m_S_out

            m_C_out = max(m_C - m_D * S_C, 0)
            m_C -= m_C_out

            # 更新形成和生长质量
            dm_form_dt = k2 * Z
            m_form += dm_form_dt * dt

            c_small = m_S_out / (n * r ** 3)

            dm_grow_dt = k3 * v_avg * c_small * (m_S_out ** (2/3))
            m_grow += dm_grow_dt * dt

            # 计算孔隙率
            integral += m_form + m_grow

        P_p = k4 * integral
        results.append(P_p)

    return np.array(results)

X_data = np.array([df["温度"], df["湿度"], df["固含量"]])
y_data = df["孔面积占比"].values

# 参数取值范围
param_bounds = ([-1000., -1000., -1000., -1000., 0.001], [1000., 1000., 1000., 1000., 1.])

# 拟合模型（初始猜测）
popt, pcov = curve_fit(model_evaporation, X_data, y_data, p0=[0.1, 0.1, 0.1, 0.1, 0.5], bounds=param_bounds)
k1_fit, k2_fit, k3_fit, k4_fit, kh_fit = popt

# 预测与评估
y_pred = model_evaporation(X_data, k1_fit, k2_fit, k3_fit, k4_fit, kh_fit)

# 计算性能指标
from sklearn.metrics import r2_score, mean_squared_error
r2 = r2_score(y_data, y_pred)
rmse = np.sqrt(mean_squared_error(y_data, y_pred))

# 输出结果
print("拟合参数：")
print(f"k1 = {k1_fit:.4f}, k2 = {k2_fit:.4f}, k3 = {k3_fit:.4f}, k4 = {k4_fit:.4f}, kh = {kh_fit:.4f}")
print(f"R² = {r2:.4f}")
print(f"RMSE = {rmse:.4f}")