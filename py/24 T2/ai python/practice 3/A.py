# 从键盘输入一个人名
name = input()

# 1 请定义一个名为Person的类及其初始化方法，在初始化方法中有一个参数name，用于初始化对象obj的姓名obj.name
########## Begin #######
class Person:
    def __init__(self, name):
        self.name = name
########## End #######

# 2 请调用Person类构造一个p1对象，p1.name为name变量（name是在第一行代码键盘输入的）
########## Begin #######
p1 = Person(name)
########## End #######
print(p1.name)

# 3 请在下面给Person2类添加一个show方法，该方法会print出：Hello Lucy! （假设对象姓名self.name为Lucy）
class Person2(Person):
    ########## Begin #######
    def show(self):
        print(f'Hello {name}!')
    ########## End #######

# 4 请调用Person2类构造一个p2对象，p2.name为name（name是在第一行代码键盘输入的），接着调用p2的show方法。
########## Begin #######
p2 = Person2(name)
p2.show()
########## End #######