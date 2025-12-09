import numpy as np
from scipy.stats import norm

# 假设这是你的数据集
data = [0.091, 0.267, 0.057, 0.099, 0.161, 0.198, 0.370]
#  0.091, 0.267, 0.057, 0.099, 0.161, 0.198, 0.370
# 0.460, 0.376, 0.264, 0.318, 0.215, 0.237, 0.149, 0.211
# 计算均值
mean_value = np.mean(data)

# 计算方差
variance = np.var(data, ddof=0)  # ddof=0 表示使用总体方差公式
# 0.565
#0.035652375
std_dev = np.sqrt(variance)  # 计算标准差

print(f"均值（平均值）: {mean_value}")
print(f"方差: {variance}")
print(f"标准差: {std_dev}")

# 构建正态分布
dist = norm(loc=mean_value, scale=std_dev)

# 计算给定点的概率密度函数值
points = [0.460]  # 你可以在这里添加任何你想要计算的点
for point in points:
    probability_density = dist.pdf(point)
    print(f"点 {point} 的概率密度函数值: {probability_density}")
