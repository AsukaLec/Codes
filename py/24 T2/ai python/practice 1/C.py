#********** Begin *********#
import math  # 导入math模块

m = int(input())  
n = int(input())  

radius_of_m = math.floor(m*2.54)/2 
radius_of_n = math.floor(n*2.54)/2

num = math.ceil((math.pi * radius_of_m ** 2) / (math.pi * radius_of_n ** 2))
print(num) 