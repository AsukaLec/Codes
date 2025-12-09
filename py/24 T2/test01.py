# print(123)
# print ("fucku")
# print(-8%2.5)

# x=int(input())
# y=int(input())
# def addnew (x):
#     def add (y):
#         return x+y
#     return add

# print(addnew(x)(y))


# x=int(input())
# y=int(input())

# def add1(x,y):
#     return x+y

# print(add1(x,y))

# print(list(filter(lambda x: x%3==0, [1,9,55,150,3,78,28,123])))

import turtle

# 定义绘制单段的函数
def drawLine(draw):
    turtle.pendown() if draw else turtle.penup()
    turtle.fd(40)
    turtle.right(90)

# 定义绘制数字的函数
def drawDigit(d):
    # 绘制七段数码管的七段
    drawLine(True) if d in [2, 3, 4, 5, 6, 8, 9] else drawLine(False)  # A
    drawLine(True) if d in [0, 1, 3, 4, 5, 6, 7, 8, 9] else drawLine(False)  # B
    drawLine(True) if d in [0, 2, 3, 5, 6, 8, 9] else drawLine(False)  # C
    drawLine(True) if d in [0, 2, 6, 8] else drawLine(False)  # D
    turtle.left(90)
    drawLine(True) if d in [0, 4, 5, 6, 8, 9] else drawLine(False)  # E
    drawLine(True) if d in [0, 2, 3, 5, 6, 7, 8, 9] else drawLine(False)  # F
    drawLine(True) if d in [0, 2, 3, 5, 6, 8, 9] else drawLine(False)  # G
    turtle.left(180)
    turtle.penup()
    turtle.fd(20)

# 设置初始位置
turtle.penup()
turtle.goto(-150, 0)
turtle.pendown()

# 绘制一个数字
drawDigit(2)
drawDigit(0)
drawDigit(2)
drawDigit(4)
drawDigit(0)
drawDigit(9)
drawDigit(0)
drawDigit(8)

# 隐藏海龟图标，完成绘制
turtle.hideturtle()
turtle.done()


##### funnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnny
import turtle
import datetime

def drawLine(draw):  # 绘制单段数码管
    turtle.pendown() if draw else turtle.penup()
    turtle.fd(40)
    turtle.right(90)

def drawDigit(d):  # 根据数字绘制七段数码管
    drawLine(True) if d in [2, 3, 4, 5, 6, 8, 9] else drawLine(False)  # A
    drawLine(True) if d in [0, 1, 3, 4, 5, 6, 7, 8, 9] else drawLine(False)  # B
    drawLine(True) if d in [0, 2, 3, 5, 6, 8, 9] else drawLine(False)  # C
    drawLine(True) if d in [0, 2, 6, 8] else drawLine(False)  # D
    turtle.left(90)
    drawLine(True) if d in [0, 4, 5, 6, 8, 9] else drawLine(False)  # E
    drawLine(True) if d in [0, 2, 3, 5, 6, 7, 8, 9] else drawLine(False)  # F
    drawLine(True) if d in [0, 2, 3,  6, 8, 9] else drawLine(False)  # G
    turtle.left(180)
    turtle.penup()
    turtle.fd(20)

def drawDate(date):  # 绘制日期
    for i in date:
        if i == '-':  # 如果是日期中的分隔符，跳过
            turtle.write('年', font=("Arial", 18, "normal"))
            turtle.fd(40)
        elif i == '=':
            turtle.write('月', font=("Arial", 18, "normal"))
            turtle.fd(40)
        elif i == '+':
            turtle.write('日', font=("Arial", 18, "normal"))
            turtle.fd(40)
        else:
            drawDigit(eval(i))  # 绘制数字
            turtle.fd(20)

# 设置初始位置
turtle.penup()
turtle.goto(-300, 0)
turtle.pendown()
turtle.setup(800, 350, 200, 200)

# 获取当前日期并格式化
date = datetime.datetime.now().strftime("%Y-%m=%d+")
drawDate(date)  # 绘制日期

# 隐藏海龟图标，完成绘制
turtle.hideturtle()
turtle.done()   
####


# s = set (range(0,5))
# s.add(114514)
# print (s)

# import numpy as np
# print(np.info(np.add))