# # -*- coding:utf-8 -*-
# import random
# people_guess = [ x for x in map( str, input("").split(",") ) ]
# computer_lst = ["石头","剪刀","剪刀","布","布","石头","布"] # 电脑出拳的方式
# computer_win_condition = [["布","石头"],["石头","剪刀"],["剪刀","布"]] # 每次电脑赢的情况
# balance_condition = [["布","布"],["石头","石头"],["剪刀","剪刀"]] # 每次平局的情况
# computer_win_number = 0 # 电脑赢的次数
# people_win_number = 0   # 玩家赢得次数

# #********* Begin *********#

# #********* End *********#

# # 游戏进行 7 次之后，进行输赢的判别
# if computer_win_number > people_win_number:
# 	print("电脑赢!",end="")
# elif computer_win_number < people_win_number:
# 	print( "玩家赢!", end="" )
# else:
# 	print("平局!") 


# -*- coding:utf-8 -*-

import random
people_guess = [ x for x in map( str, input("").split(",") ) ]
computer_lst = ["石头","剪刀","剪刀","布","布","石头","布"] # 电脑出拳的方式
computer_win_condition = [["布","石头"],["石头","剪刀"],["剪刀","布"]] # 每次电脑赢的情况
balance_condition = [["布","布"],["石头","石头"],["剪刀","剪刀"]] # 每次平局的情况
computer_win_number = 0 # 电脑赢的次数
people_win_number = 0   # 玩家赢得次数

#********* Begin *********#
for i in range(7):
    people_choice = people_guess[i].strip()  # 获取玩家的出拳，并去除可能的空格
    computer_choice = computer_lst[i]  # 获取计算机的出拳

    # 判断胜负
    if [computer_choice, people_choice] in computer_win_condition:
        computer_win_number += 1
        
    elif [computer_choice, people_choice] in balance_condition:
        computer_win_number += 0 
        people_win_number += 0 
    else:
        people_win_number += 1
    

    # 如果有一方已经赢得4局，提前结束游戏
    if computer_win_number == 4 or people_win_number == 4:
        break
#********* End *********#

# 游戏进行 7 次之后，进行输赢的判别
if computer_win_number > people_win_number:
    print("电脑赢!", end="")
elif computer_win_number < people_win_number:
    print("玩家赢!", end="")
else:
    print("平局!")