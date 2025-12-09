# coding=utf-8

# 创建并初始化munu_list列表
menu_list = []
while True:
    food = input()
    if not food:
        break
    menu_list.append(food)

# 请在此添加代码，对menu_list进行元祖转换以及元祖计算等操作，并打印输出元祖及元祖最大的元素
########## Begin ##########
menu_tuple=tuple(menu_list)
print(menu_tuple)
########## End ########## 

# 寻找菜单中首字母最小的元素，输出其索引和值。
########## Begin ##########
print(max(menu_tuple))

min_element = min(menu_tuple)
min_index = menu_tuple.index(min_element)
print(min_index)
print(min_element)
########## End ########## 
# s =[]
# for i in range(len(menu_list)):
#     s.append(menu_list[i][0])
# s.sort()

# for i in range(len(menu_list)):
#     if menu_tuple[i][0] == s[len(menu_list)-1]:
#         print(menu_list[i])
#         break

# for i in range(len(menu_list)):
#     if menu_tuple[i][0] == s[0]:
#         print(i)
#         print(menu_list[i])
#         break
# print(max(menu_tuple))

# min_element = min(menu_tuple)
# min_index = menu_tuple.index(min_element)
# print(min_index)
# print(min_element)