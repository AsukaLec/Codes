#********** Begin *********#

import math


radius = 6371 * 1000
# 1. 计算地球表面积（表面积公式S = 4πR2）
surface_area = 4 * math.pi * radius * radius
print(f'地球表面积为{surface_area}平方米')

# 2. 计算地球体积（体积公式是V = 4πR3/3）
volume = 4 * math.pi * radius * radius * radius / 3
print(f'地球体积为{volume:.2f}立方米')

# 3. 计算地球赤道的周长（圆周长公式是L = 2πR）
circumference = 2 * math.pi * radius
print(f'地球赤道周长为{circumference:.2f}米')

# 4.计算绳子与地球之间的空隙大小
previous_length = math.pi * 2 * radius
current_length = previous_length +1
space = current_length / 2 / math.pi - radius
print(f'空隙大小为{space:.2f}米')  # 结果保留2位小数
#********** End *********#
# 5.判断老鼠是否可以从空隙中钻过
if space * 100 > 10:
    print('老鼠可以从空隙中钻过')
else:
    print('老鼠无法通过空隙')