# for i in "CHINA":
#     for k in range(2):
#         print (i,end="")
#         if i== 'N':
#             break

# for i in range(3):
#     for s in "abcd":
#         if s == "c":
#             break
#         print (s,end="")

# t = "Python"
# print ( t if t >= "python" else "None")

# a,b=0,1
# while a<=100:
#     print(a,end=" ")
#     a,b=b,a+b

# for i in range(1,21,5):
#     print(i,end=" ")

# print (5 if 5>6 else (6 if 3>2 else 5))

# T 17
# for i in range (1,10):
#     for j in range (1,10):
#         if j<i:
#             print(" "*7,end="")                                                                                        
#         else :
#             sum = int(i)*int(j)
#             print("{0}*{1}={2:<2}".format(i,j,sum),end=" ")
#     print (end="\n")

# T18
# a,b=0,1
# while a<=100:
#     print(a,end=" ")
#     a,b=b,a+b

# T 19
# str = input()
# sum = 0
# str1 = [7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2]
# str2 = [1,0,10,9,8,7,6,5,4,3,2]
# for i in range(17):
#     sum += int(str[i])*int(str1[i])
# sum = sum %11
# ans = str2[sum]
# print (ans)
# if ans<10 and int(str[17])==ans:
#     print(str,end="")
#     print("是合法的身份证号")
    
# elif ans==10 and int(str[17])=='X':
#     print(str,end="")
#     print("是合法的身份证号")
    
# else:
#     print(str,end="")
#     print("不是合法的身份证号")
    
# T 20
# import random
# while True:
#     length = int(input())
#     if length <0:
#         break
#     s = ""
#     for i in range(length):
#         pos = int(random.randint(0,2))
#         if pos==0:
#             s += str(random.randint(0,10))
#         else :
#             s += random.choice('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ')
#     print(s)

# T 21
# str = int(input())
# a = str % 10
# b = int((str % 100 - a)/10)
# c = str // 100
# print(c,end=" ")
# print(b,end=" ")
# print(a,end=" ")

# T 22
# times = 0
# for i in range(100,201):
#     if times ==10 :
#         print("\n")
#         times = 0
#     if i%3 != 0 :
#         times += 1
#         print(i,end=" ")

# T 23
# times = 3
# while times :
#     gender = input("请输入您的性别,m代表男生,f代表女生: ")
#     age = int(input("请输入您的年龄: "))
    
#     if gender == 'm':
#         if age > 18 and age <=22 :
#             print("True")
#         else :
#             print("False")
#     else :
#         if age > 17 and age <= 21 :
#             print("True")
#         else :
#             print("False")
#     times -= 1

# T 24
# str = input()
# pos = str.find(' ')
# year = int(str[:pos])
# month = int(str[pos:])

# condition = 0
# if year % 4 == 0 and year % 100 != 0 :
#     condition = 1 
# elif year % 4 == 0 and year % 100 == 0 and year % 400 != 0 :
#     condition = 0
# elif year % 4 == 0 and year % 100 != 0 and year % 400 == 0 :
#     condition = 1
# elif year % 4 != 0 :
#     condition = 0

# if condition == 1 :
#     if month == 1 or month == 3 or month == 5 or month == 7 or month == 8 or month == 10 or month == 12 :
#         print(31)
#     elif month != 2 :
#         print(30)
#     else :
#         print(29)
# else :
#     if month == 1 or month == 3 or month == 5 or month == 7 or month == 8 or month == 10 or month == 12 :
#         print(31)
#     elif month != 2 :
#         print(30)
#     else :
#         print(28)

# T 25
# length = int(input())
# gap = int(input())
# list1 = list(range(length))
# total = length - 1

# for i in range (length) :
#     list1[i] += 1

# pos = 0  
# while len(list1) > 1:
#     pos = (pos + gap - 1) % len(list1)
#     list1.pop(pos)

# print(list1[0])


#  T josephur nb
# n = int(input("Please number of monkeys:"))
# m = int(input("Please input the index:"))   
# idx = 0
# i = 2
# while i <= n:
#     idx = (idx + m) % i
#     i += 1
    
# result = idx + 1
# print(result)

