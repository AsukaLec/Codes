import matplotlib.pyplot as plt
from scipy.spatial import ConvexHull
import numpy as np

# 设置matplotlib支持中文显示
plt.rcParams['font.sans-serif'] = ['SimHei']  # 指定默认字体为SimHei
plt.rcParams['axes.unicode_minus'] = False    # 解决保存图像是负号'-'显示为方块的问题

# 定义点的坐标和所属簇
points = {
    'A1': {'coords': (2, 10), 'cluster': 1},
    'A2': {'coords': (2, 5), 'cluster': 2},
    'A3': {'coords': (8, 4), 'cluster': 2},
    'B1': {'coords': (5, 8), 'cluster': 1},
    'B2': {'coords': (7, 5), 'cluster': 2},
    'B3': {'coords': (6, 4), 'cluster': 2},
    'C1': {'coords': (1, 2), 'cluster': 2},
    'C2': {'coords': (4, 9), 'cluster': 1}
}

# 提取所有点的坐标
all_x_coords = [point['coords'][0] for point in points.values()]
all_y_coords = [point['coords'][1] for point in points.values()]
clusters = [point['cluster'] for point in points.values()]
labels = list(points.keys())

# 绘制所有点
plt.figure(figsize=(8, 6))
colors = ['red', 'blue', 'green', 'orange', 'purple', 'brown', 'pink', 'gray', 'olive', 'cyan']
for i, cluster in enumerate(set(clusters)):
    cluster_points = [(x, y) for j, (x, y) in enumerate(zip(all_x_coords, all_y_coords)) if clusters[j] == cluster]
    plt.scatter(*zip(*cluster_points), color=colors[i % len(colors)], label=f'簇{cluster}')

# 计算每个簇的中心点并绘制
for i, cluster in enumerate(set(clusters)):
    cluster_points = np.array([[p['coords'][0], p['coords'][1]] for p in points.values() if p['cluster'] == cluster])
    if len(cluster_points) > 0:
        centroid = cluster_points.mean(axis=0)
        plt.scatter(*centroid, color=colors[i % len(colors)], marker='x', s=100, label=f'簇{cluster}中心点' )
        print(f'簇{cluster}中心点坐标: ({centroid[0]:.2f}, {centroid[1]:.2f})')

# 为每个簇绘制凸包
for i, cluster in enumerate(set(clusters)):
    cluster_points = np.array([[p['coords'][0], p['coords'][1]] for p in points.values() if p['cluster'] == cluster])
    if len(cluster_points) > 2:  # 至少需要3个点来构建凸包
        hull = ConvexHull(cluster_points)
        hull_points = cluster_points[hull.vertices]
        plt.fill(*zip(*hull_points), alpha=0.2, color=colors[i % len(colors)])

# 设置图表标题和坐标轴标签
plt.title('最终聚类结果')
plt.xlabel('X坐标')
plt.ylabel('Y坐标')

# 显示图例
plt.legend()

# 显示图表
plt.grid(True)
plt.show()
