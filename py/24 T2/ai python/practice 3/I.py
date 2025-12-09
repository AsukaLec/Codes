# 创建并初始化Guests列表
guests = []

while True:
    guest = input()
    #请在此添加代码，输入客人名字，空输入退出循环
    ########## Begin ##########
    if guest == "":
        break
    guests.append(guest)
    ########## End ########## 

	
# 请在此添加代码，对guests列表进行插入、删除等操作
########## Begin ##########
deleted_guest = guests.pop()
guests.insert(2, deleted_guest)
guests.pop(1)
########## End ########## 
print(deleted_guest)
print(guests)
# 请在此添加代码，对新的guests列表排序
########## Begin ##########
guests.sort(reverse=True)
########## End ########## 

print(guests)


# step 1：将guests列表末尾的元素删除，并将这个被删除的元素值保存到deleted_guest变量；

# step 2：将deleted_guest插入到 step 1 删除后的guests列表索引位置为2的地方；

# step 3：将 step 2 处理后的guests列表索引位置为1的元素删除；

# 打印输出 step 1 的deleted_guest变量；

# 打印输出 step 3 改变后的guests列表。

# step 4：对于新的guests列表，按照首字母从大到小的顺序进行排序，打印排序后的列表。