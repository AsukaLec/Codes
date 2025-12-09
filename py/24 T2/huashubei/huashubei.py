import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.optimize import least_squares
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

# 实验数据
data = {
    '温度': [30, 30, 30, 30, 30, 30, 30, 30, 30, 40, 40, 40, 40, 40, 40, 40, 40, 40, 50, 50, 50, 50, 50, 50, 50, 50, 50],
    '湿度': [50, 50, 50, 70, 70, 70, 90, 90, 90, 50, 50, 50, 70, 70, 70, 90, 90, 90, 50, 50, 50, 70, 70, 70, 90, 90, 90],
    '固含量': [6, 6, 6, 8, 8, 8, 10, 10, 10, 8, 8, 8, 10, 10, 10, 6, 6, 6, 10, 10, 10, 6, 6, 6, 8, 8, 8],
    '孔面积占比': [18.09, 17.04, 19.45, 9.11, 9.4, 8.85, 9.35, 9.4, 9.08, 30.33, 31.2, 29.2, 24.12, 24.34, 23.11, 36.01, 35.35, 35.66, 6.41, 6.62, 6.73, 6.41, 6.62, 6.73, 8.38, 8.3, 8.29]
}

# 读取数据
df_data = pd.DataFrame(data)


# 计算每组实验（相同 T、H、SC）对应的孔面积占比平均值
grouped = df_data.groupby(['温度', '湿度', '固含量'])['孔面积占比'].mean().reset_index()
grouped.rename(columns={'孔面积占比': '平均孔面积占比'}, inplace=True)

# 构建用于拟合的输入输出数据
X = df_data[['温度', '湿度', '固含量']].values
y = df_data['孔面积占比'].values

# 定义简化后的模型（经验形式）用于拟合
def predict_A(params, X):
    # 参数解包
    k1, k2, k3, k4, k5, k6, k7= params
    T, H, SC = X[:, 0], X[:, 1]/100, X[:, 2]  # 温度，湿度比例，固含量
    
    
    # return a * (b ** T) * (H ** c) * np.log (1 + SC) / np.log(d)
    # return a*T + b*H + c*SC + d*T*T + e*H*H + f 
    return k1 * T * T + k2 * T + k3 * H + k4 * SC + k5 * T * H + k6 * T * SC + k7

# 构建残差函数
def residuals(params, X, y):
    return predict_A(params, X) - y

# 初始参数猜测
initial_params = np.array([1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0])  # 确保 d 的初始值远离 1


# 最小二乘拟合
result = least_squares(residuals, initial_params, args=(X, y))

# 拟合结果

fitted_params = result.x
print("拟合参数：", fitted_params)


fitted_params1 = [ -0.202433 ,14.921540 , 0.358833 , -9.626111 , -0.006976 , 0.188738 , -232.016112]


# 使用拟合后的参数计算理想值
predicted_y = predict_A(fitted_params, X)

# 创建绘图
plt.figure(figsize=(12, 8))

# 绘制实际值
plt.scatter(df_data['固含量'], df_data['孔面积占比'], label='实际值', alpha=0.6, color='blue')

# 绘制理想值
plt.scatter(df_data['固含量'], predicted_y, label='理想值', alpha=0.6, color='red', marker='x')

# 添加标题和标签
plt.title('实际值与理想值对比')
plt.xlabel('固含量')
plt.ylabel('孔面积占比')
plt.legend()
plt.grid(True)
plt.show()
