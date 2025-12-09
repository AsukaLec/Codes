import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
import pandas as pd

# x = [[1, 2],
#      [3, 4]]
# y = np.concatenate([x, x], axis = 1)
# print (y)

# z = np.concatenate([x, x], axis = 0)
# print (z)

ser1 = pd.Series(['a', 'b', 'c'])
ser2 = pd.Series(['1', '222', 'fuckyou'])
ser = pd.concat([ser1, ser2])
# print(ser)
# print(ser.loc[1])

df1 = pd.DataFrame({'nmg':ser1, 'sdf':ser2})
# print(df1) 


# df = pd.concat([df1, df1], axis = 1)
# print(df)
# print()

df0 = pd.DataFrame({'wer': ser1}) 

df2 = pd.merge(df1,df0, left_on= 'nmg', right_on= 'wer').drop('wer', axis = 1)
print(df2) #删除重复列
print()




# df001 = pd.concat([df1, df1], axis = 0, ignore_index= True)#忽略重复索引
# print(df001)