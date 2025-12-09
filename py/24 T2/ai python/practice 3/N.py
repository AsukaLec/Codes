import random

s = int(input())
random.seed(s)  # 调用函数，输出结果
"""创建两个二维列表"""
lsa = []
lsb = []
for i in range(1, 6):
    lsa.append([i, random.randint(0, 100), random.randint(0, 100)])
    lsb.append([i, random.randint(0, 100)]) 
"""创建两个二维列表"""
print('原数据', lsa)
print('新增成绩', lsb)

p = int(input())#指定更新学生

"""合并列表，将lsb中成绩插入到"""
score_ls = []
########## Begin ########## 
for sublist in lsa:
    sublist.insert(p,lsb[sublist[0]-1][1])
score_ls = lsa 
########## End ########## 

"""合并列表，将lsb中成绩插入到"""
print('更新后数据', score_ls)



# k = int(input("请输入插入位置: "))  # 指定插入位置


# """合并列表，将lsb中成绩插入到"""
# score_ls = []
# ########## Begin ########## 
# for sublist in lsa:
#     if sublist[0] == p:  # 找到指定学号的子列表
#         sublist.insert(k, lsb[sublist[0] - 1][1])  # 插入q成绩到指定位置
# score_ls = lsa  # 更新后的列表
# ########## End ########## 
