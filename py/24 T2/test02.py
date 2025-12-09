# 最小维度  
import numpy as np 



dtype = [('x', 'i4'), ('y', 'i4')]

# 手动初始化数组的内容
data = [
    [(1, 2), (3, 4)],
    [(5, 6), (7, 8)]
]

z = np.array(data, dtype = dtype)
print(z[0,1]['y'])
print(z.shape)


x =  [(1,2,3)] 
a = np.asarray(x, dtype = float)  #numpy.asarray(a, dtype = None, order = None)
print (a)

#numpy 包中的使用 arange 函数创建数值范围并返回 ndarray 对象，函数格式如下：
# numpy.arange(start, stop, step, dtype)
arange = np.arange(0, 6, 1, dtype = complex)
print (arange)

#numpy.linspace 函数用于创建一个一维数组，数组是一个等差数列构成的，格式如下：
#np.linspace(start, stop, num=50, endpoint=True, retstep=False, dtype=None)
linspace = np.linspace(3, 21, 7, dtype= int)
print(linspace)

# numpy.logspace 函数用于创建一个于等比数列。格式如下：
# np.logspace(start, stop, num=50, endpoint=True, base=10.0, dtype=None)
#start	序列的起始值为：base ** start
a = np.logspace(2,6, num =  3, base = 3, dtype= float)  
print (a)


