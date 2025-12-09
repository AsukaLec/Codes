import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
import pandas as pd
array = ['ver', 'pia', 'lec', 'ham', 'aka']
data = pd.Series([1, 2, 3 ,4 ,  5], array, dtype= 'float')
print (data.values)
print (data[1:3])
print()
print(data)
print()
print(data['lec'])

driver_dict = {'nor':1,
               'pia':2,
               'ver':3,
               'lec':4,
               'ham':5
               }
driver = pd.Series(driver_dict)
print(driver)

championship = pd.DataFrame({'name':array, 'position':[1,2,3,4,5]})
print(championship)
print()

print(championship.loc[1])#loc行索引
print()
print(championship[0:])
print(championship['name'])
#切片不能访问列，索引不能访问行

# nb1 = Image.open('./py/pyai/114514.jpg')

# plt.subplot(121)
# plt.imshow(nb1)
# nb = np.array(nb1)

# offset = 1
# for i in range(540):
#     for j in range(380):
#         if i % 2 == 0:
#             nb[i, j, :] = [255, 255, 255]
# for i in range(540):
#     for j in range(380):
#         if j % 2 == 0:
#             nb[i, j, :] = [255, 255, 255]
            



# plt.subplot(122)
# plt.imshow(nb)
# plt.show()


# a = np.array([[1, 2, 3],
#               [4, 5, 6]], dtype = 'int8' )
# b = np.ones((2, 3), dtype = 'int8')

# np.add(a, b, a)
# print (a)