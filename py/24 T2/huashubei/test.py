# import heapq

# def huffman_encoding(frequencies):
#     # 构造Huffman树
#     heap = [[weight, [symbol, ""]] for symbol, weight in frequencies.items()]
#     heapq.heapify(heap)
#     while len(heap) > 1:
#         lo = heapq.heappop(heap)
#         hi = heapq.heappop(heap)
#         for pair in lo[1:]:
#             pair[1] = '0' + pair[1]
#         for pair in hi[1:]:
#             pair[1] = '1' + pair[1]
#         heapq.heappush(heap, [lo[0] + hi[0]] + lo[1:] + hi[1:])
#     # 返回Huffman编码
#     return sorted(heapq.heappop(heap)[1:], key=lambda p: (len(p[-1]), p))

# def count_zeros(frequencies, encoding):
#     # 计算'0'的个数
#     zeros = 0
#     for symbol, code in encoding:
#         zeros += frequencies[symbol] * code.count('0')
#     return zeros

# def solve():
#     T = int(input())
#     for _ in range(T):
#         S = int(input())
#         frequencies = list(map(int, input().split()))
#         E = int(input())
#         # 构造Huffman编码
#         encoding = huffman_encoding({i: freq for i, freq in enumerate(frequencies)})
#         # 计算'0'的个数
#         zeros = count_zeros({i: freq for i, freq in enumerate(frequencies)}, encoding)
#         # 判断是否满足条件
#         if zeros == E:
#             print("Yes")
#         else:
#             print("No")
            
# def main():
#     solve()



# def fun(a): 
#     b = a+8 

# b = 520
# fun(b) 
# print(b) 

# 日内瓦 = int(114514)
# print(日内瓦)
# amd = pow(2, 1145)
# print ((pow(55, 33) > pow (66, 22)))

# print ( 0x10)

# print (pow(2, 114514, 10000000))


# a = [1, 2, 3, 4, 5]
# print(max(a))
# s = "mygo"
# y = 'mujika'
# print('what if %s ' % (s))

# a="Python等级考试" 
# b="=" 
# c=">" 
# print("{0:{1}{3}{2}}".format(a,b,25,c))


# x=True 
# y=False
# print(True and y )

# print (4 ** 3 + 7 ** 3)

# def f1 () :
#     f2()

# def f2():
#     print (114514)

# def main():
#     f1()
#     f2()

# main()
# print ('y' < 'x' == False)
# list1 = list(map(lambda x:2*x+1, range(5)))
# print (list1)

# list2 =  dict(map(lambda x: (x%5,x) , range(500)))
# print (list2)


import numpy as np
import pandas as pd
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt
from sklearn.metrics import r2_score, mean_squared_error

# 设置字体和显示参数
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

# 原始实验数据
data = {
    '温度': [30, 30, 30, 30, 30, 30, 30, 30, 30, 40, 40, 40, 40, 40, 40, 40, 40, 40, 50, 50, 50, 50, 50, 50, 50, 50, 50],
    '湿度': [50, 50, 50, 70, 70, 70, 90, 90, 90, 50, 50, 50, 70, 70, 70, 90, 90, 90, 50, 50, 50, 70, 70, 70, 90, 90, 90],
    '固含量': [6, 6, 6, 8, 8, 8, 10, 10, 10, 8, 8, 8, 10, 10, 10, 6, 6, 6, 10, 10, 10, 6, 6, 6, 8, 8, 8],
    '孔面积占比': [18.09, 17.04, 19.45, 9.11, 9.4, 8.85, 9.35, 9.4, 9.08, 30.33, 31.2, 29.2, 24.12, 24.34, 23.11, 36.01, 35.35, 35.66, 6.41, 6.62, 6.73, 6.41, 6.62, 6.73, 8.38, 8.3, 8.29]
}

# 转换为 DataFrame
df = pd.DataFrame(data)

# 固定参数
r = 1.0    # 半径假设单位为1
p_D = 0.944 # DMF 密度
p_S = 1.260 # 环丁砜密度
p_C = 1.500 # 纤维素的密度
k_B = 1.38e-23 # 玻尔兹曼常数
S_S = 0.15     # 固体饱和度
S_C = 0.01     # 恒量饱和度
n = 5       # 分子数量
t_evap = 100  # 蒸发时间
dt = 2      # 时间差

# 蒸发过程模型函数（修改后的）
def model_evaporation(X, k1, k2, k3, k4, kh):
    T, H, SC = X
    results = []

    for i in range(len(T)):
        temp = T[i]
        humidity = H[i]
        sc = SC[i]
        
        # 初始化变量
        m_D = 24  # 初始液滴质量
        m_S = 6   # 固体质量
        m_C = sc * 0.3  # 恒量质量

        num_steps = int(t_evap / dt)
        time_points = np.linspace(0, t_evap, num_steps)

        # 时间步的处理过程
        for t in time_points:
            phi_c = m_C / p_C * (m_C / p_C + m_D / p_D + m_S / p_S + m_C / p_C)
            
            # 浓度计算
            V = m_S / p_S + m_D / p_D
            c = (m_S + m_D) / V

            # 饱和蒸汽压计算
            P_sat = 10 ** (6.09451 - 2725.96 / temp + 28.209 + 273.15) * 100000  
            
            # 更新液滴质量
            dm_D_dt = - k1 * P_sat * c * (1 - (humidity * kh))  
            m_D += dm_D_dt * dt

            # 粘度和扩散系数计算
            eta = 1 + 2.5 * phi_c
            D = (k_B * temp) / (6 * np.pi * eta * r * 1e-22)

            # 计算平均速度和Z
            v_avg = np.sqrt(D)
            Z = np.sqrt(2 * n * np.pi * r**2 * v_avg)

            # 更新质量
            m_S_out = np.maximum(m_S - m_D * S_S, 0)
            m_C_out = np.maximum(m_C - m_D * S_C, 0)
            m_S -= m_S_out
            m_C -= m_C_out

            m_form = k2 * Z
            c_small = m_S_out / (n * r ** 3)
            m_grow = k3 * v_avg * c_small * (m_S_out ** (2/3))

            # 孔隙率积分
            integral = m_form + m_grow

            # 计算P_p
            P_p = k4 * integral
            results.append(P_p)
        
        # 返回每组数据的最终结果（每个样本的预测孔面积占比）
        final_result = np.mean(results)
        results.clear()
        
    return np.array(final_result)

# 输入数据
X_data = np.array([df["温度"], df["湿度"], df["固含量"]])
y_data = df["孔面积占比"].values

# 设置拟合参数的范围
param_bounds = ([-1000., -1000., -1000., -1000., 0.001], [1000., 1000., 1000., 1000., 1.])

# 拟合模型
popt, pcov = curve_fit(model_evaporation, X_data, y_data, p0=[0.1, 0.1, 0.1, 0.1, 0.5], bounds=param_bounds)

# 提取拟合参数
k1_fit, k2_fit, k3_fit, k4_fit, kh_fit = popt

# 预测与评估
y_pred = model_evaporation(X_data, k1_fit, k2_fit, k3_fit, k4_fit, kh_fit)

# 计算性能指标
r2 = r2_score(y_data, y_pred)
rmse = np.sqrt(mean_squared_error(y_data, y_pred))

# 输出拟合结果
print("拟合参数：")
print(f"k1 = {k1_fit:.4f}, k2 = {k2_fit:.4f}, k3 = {k3_fit:.4f}, k4 = {k4_fit:.4f}, kh = {kh_fit:.4f}")
print(f"R² = {r2:.4f}")
print(f"RMSE = {rmse:.4f}")

# 可视化
plt.figure(figsize=(15, 5))

# 第一张图：温度 vs 孔面积占比
plt.subplot(1, 3, 1)
plt.scatter(df["温度"], y_data, c='blue', label='实际值', marker='o')
plt.scatter(df["温度"], y_pred, c='red', label='预测值', marker='x')
plt.xlabel('温度')
plt.ylabel('孔面积占比')
plt.title('温度 与 孔面积占比')
plt.legend()
plt.grid(True)

# 第二张图：湿度 vs 孔面积占比
plt.subplot(1, 3, 2)
plt.scatter(df["湿度"], y_data, c='blue', label='实际值', marker='o')
plt.scatter(df["湿度"], y_pred, c='red', label='预测值', marker='x')
plt.xlabel('湿度')
plt.ylabel('孔面积占比')
plt.title('湿度 与 孔面积占比')
plt.legend()
plt.grid(True)

# 第三张图：固含量 vs 孔面积占比
plt.subplot(1, 3, 3)
plt.scatter(df["固含量"], y_data, c='blue', label='实际值', marker='o')
plt.scatter(df["固含量"], y_pred, c='red', label='预测值', marker='x')
plt.xlabel('固含量')
plt.ylabel('孔面积占比')
plt.title('固含量 与 孔面积占比')
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()
