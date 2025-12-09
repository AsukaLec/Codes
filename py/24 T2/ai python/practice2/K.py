#1 请在下面定义一个名为happy的函数，已经给出了函数内部的语句print('Happy Birthday!')，happy函数没有输入参数和返回值。
########## Begin #######
def happy():
    print('Happy Birthday!')
########## End ##########

#2 请在这里调用上面定义好的happy函数
########## Begin ####### 

########## End ##########
happy()

#3 happy2是一个带返回值的函数，返回值为'Happy Birthday!'
def happy2():
########## Begin #######
    return 'Happy Birthday!'
########## End ##########

#4 调用happy2函数，将其返回值赋值给一个变量info
########## Begin #######
info = happy2()
########## End ##########
print(info)

#5 happy3是一个带输入参数、带返回值的函数，输入参数person是一个表示人名的字符串，函数会返回一个字符串'Happy Birthday! Dear Lucy.'（假设person为Lucy的情况）
########## Begin #######
# 'Happy Birthday! Dear Lucy.'
def happy3(person):
    return 'Happy Birthday! Dear '+person+"."

########## End ##########

person = input()
print(happy3(person))