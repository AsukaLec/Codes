class Animal():
    def __init__(self, name):
        self.name = name
    def breath(self):
        print(f'{self.name}在呼吸。')
    def eat(self):
        print(f'{self.name}在进食。')
        
# 请在下面填入定义Fish类的代码，fish类继承自animals类，有一个swim方法输出print(f"{self.name}可以游泳。")
########## Begin ##########
class Fish(Animal):
    def swim(self):
        print(f"{self.name}可以游泳。")
########## End ##########  

# 请在下面填入定义Bird类的代码，Bird类继承自Animal类，有一个方法fly输出print(f"{self.name}可以飞翔。")，有一个eat方法print(f"{self.name}可以吃鱼。")
#********** Begin *********#
class Bird(Animal):
    def fly(self):
        print(f"{self.name}可以飞翔。")
    def eat(self):
        print(f"{self.name}可以吃鱼。")
########## End ##########  
		
fName = input()
f = Fish(fName)
f.breath()
f.swim()
f.eat()

bName = input()
b = Bird(bName)
b.breath()
b.fly()
b.eat()