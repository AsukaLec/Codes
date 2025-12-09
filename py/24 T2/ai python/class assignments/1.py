# 定义一个学生类,包括学号、姓名和出生日期三个属性(数据成员);包括一个用于给定数据成员初始值的构造函数;包含一个可计算学生年龄的方法。编写该类并对其进行测试。(要求调用datetime模块获取当前年份)
# from datetime import date
# class Student :
#     def __init__(self, id1, name, borntime):
#         self.name = name
#         self.id1 = id1
#         self.borntime = borntime
#     def showage(self):
#         current = date.today()
#         bornyear = int(borntime[0:4])
#         print(current.year - bornyear)


# while(True):
#     id1 = input()
#     name = input()
#     borntime = input()
#     student1 = Student(id1, name, borntime)
#     student1.showage()

# current_date = date.today()
# print(current_date.year)


# # # 获取当前年份
# current_year = datetime.datetime.month()
# print(current_date)
# print(current_year)



# 使用python创建一个动物父类,创建牛和羊两个子类,根据输入的动物种类和名字输出语句。 
# 输入:第一行输入”cow” or “sheep”,第二行输入他的名字 输出:“name”+” says "muu"” or” says "mee"”

# class Animal:
#     def __init__(self,name,kind):
#         self.name = name
#         self.kind = kind

# class Cow(Animal):
#     def __init__(self,name,kind):
#         Animal.__init__(self,name,kind)
#     def muu(self):
#         print(" {0} says muu ".format(name) )

# class Sheep(Animal):
#     def __init__(self,name,kind):
#         Animal.__init__(self,name,kind)
#     def mee(self):
#         print(" {0} says mee ".format(name) )

# while(True):
#     kind = input()
#     name = input()

#     if kind == "cow":
#         cow = Cow(name, kind)
#         cow.muu()
#     else :
#         sheep = Sheep(name,kind)
#         sheep.mee()
        
# name = input()
# print("yes{0}".format(name))


# Animal类有私有属性__name,给Animal类编写一个
# 可以重新设置私有属性__name的方法setName,
# class Animal:
#     def __init__(self, name):
#         self.__name = name 

#     def setName(self, new_name):
#         if len(new_name) < 10:  
#             self.__name = new_name  
#             print(f"I'm {self.__name}")  
        
# while(True):
#     name = input()
#     animal = Animal(name)
#     new_name = input()
#     animal.setName(new_name)


# 请创建一个BankAccount类,并用它创建一个实例,实现取钱和存钱的功能。
# 输入:第一行为一个浮点数,表示账户余额;
# 之后3行每行一个符号、一个空格、一个数字。“+“代表存钱,”-“代表取钱。
# 每次读入后,输出账户的余额。
class BankAccount:
    def __init__(self,balance):
        self.balance = balance
    def savemoney(self,money):
        self.balance += money
        print(self.balance)
    def putoffmoney(self,money):
        self.balance -= money
        print(self.balance)

balance = int(input())
accout = BankAccount(balance)
while(True):
    lines = input()
    opt = lines[0]
    money = int(lines[2:])

    if opt == '+':
        accout.savemoney(money)
    else:
        accout.putoffmoney(money)
