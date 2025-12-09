# print(type(eval('45')))

# def fun1():
#     print("in fun1()")
#     fun2()

# def fun2():
#     print("in fun2()")
#     fun1()

# fun1()
# fun2()

# def fun(x,y="name",z="No"):
#     pass
# fun(x=1,y=2,3)

# img1=[12,34,56,78]
# img2=[1,2,3,4,5]
# def display():
#     print(img1)
# def modify():
#     img1= img2 
# modify()
# # display()

# da = [1,2,3]
# print(id(da))
# def getda(st):
#     fa = da.copy()
#     print(id(fa))
# getda(da)

# def hub(ss,x=2.0,y=4.0):
#     ss += x*y
# ss = 10
# print (ss,hub(ss,3))

# def test (b=2,a=4):
#     global z
#     z+=a*b
#     return z

# z=10
# print(z,test(   ))

# ls=[]
# def func(a,b):
#     ls.append(b)
#     return a*b
# s=func("Hello!",2)
# print(s,ls)

# n=2
# def fff(x,y=10):
#     global n
#     return x*y*n
# s = fff(10,2)
# print(s)

# def gcd(x,y):
#     if x<y :
#         x,y=y,x
#     while x%y!=0 :
#         r=x%y
#         x=y
#         y=r
#     return y
# a=int(input())
# b=int(input())
# print(gcd(a,b))

# g= lambda x,y=3,z=5:x*y*z
# print(g(1))

# def runnian(year):
#     if (year%4==0 and year%100!=0) or year%400==0:
#         print("True")
#     else:
#         print("False")
# year=int(input())
# runnian(year)

# def judge(str):
#     length = len(str)
#     upper_num = 0
#     lower_num = 0
#     for i in range(length):
#         if str[i].isupper():
#             upper_num+=1
#         elif str[i].islower():
#             lower_num+=1
#     return upper_num,lower_num
# str=input()
# print(judge(str))

def judge(list):
    length=len(list)
    list.sort()
    return list[0],list[length-1]

list=[1,4,5,2,9]
print(judge(list))