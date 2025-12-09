# 定义一个汽车类
class Car:
    """ 汽车类，包含制造商、型号、年份、价格四个属性"""
    def __init__(self, make, model, year, price):
        self.__make = make
        self.__model = model
        self.__year = year
        self.__price = price

    def get_make(self):
        """获取汽车制造商"""
        return self.__make 

    def get_model(self):
        """获取汽车型号"""
        return self.__model 

    def get_year(self):
        """获取汽车年份"""
        return self.__year 

    def get_price(self):
        """获取汽车价格"""
        return self.__price

    def set_price(self, new_price):
        """更新汽车价格"""
        self.__price = new_price

    def __str__(self):
        """返回汽车的描述信息"""
        return f"{self.__year} {self.__make} {self.__model} - 价格：{self.__price}元"

# 创建一个汽车销售系统，多家门店多个系统
class CarSalesSystem:
    def __init__(self):
        self.cars = []
        self.salespersons = []

    def add_car(self, car):
        self.cars.append(car)

    def add_salesperson(self, salesperson):
        self.salespersons.append(salesperson)

    def sell_car(self, car_index, salesperson):
        if 0 <= car_index < len(self.cars):
            car = self.cars.pop(car_index)
            salesperson.sell_car(car)
        else:
            print("无效的汽车索引！")

    def __str__(self):  # 打印所有库存
        outStr = ''
        for car in self.cars: 
            outStr += str(car) + '\n'
        return '现有库存车，如下：\n' + outStr

class Person:
    def __init__(self, name, ID, level):
        self.name = name
        self.ID = ID
        self.level = level

# 定义一个经理类，负责管理销售价格
class Manager(Person):  
    def __init__(self, name, ID, level):
        super().__init__(name, ID, level)

    def input_car(self, sellSys: CarSalesSystem):
        # 一次性输入多辆车的信息
        info = input().split()
        for i in range(0, len(info), 4):
            make, model, year, price = info[i], info[i+1], int(info[i+2]), float(info[i+3])
            car = Car(make, model, year, price)
            sellSys.add_car(car)

    def set_price(self, car, new_price):
        car.set_price(new_price)

# 定义一个销售员类
class Salesperson(Person):
    def __init__(self, name, ID, level, commission_rate, store):
        super().__init__(name, ID, level)
        self.commission_rate = commission_rate
        self.commission = 0
        self.sellList = []  # 用于存储销售的汽车对象
        self.store = store

    def sell_car(self, car):
        self.sellList.append(car)
        comm = car.get_price() * self.commission_rate
        self.commission += comm
        print(f"{self.name}销售了一辆{car.get_make()} {car.get_model()}，获得佣金{comm:.1f}元。")

if __name__ == '__main__':
    store1 = CarSalesSystem()  # 1号店销售系统

    manager1 = Manager('老王', '001', 'Manager')

    seller1 = Salesperson('小张', '101', 'Seller', 0.01, store1)
    seller2 = Salesperson('小明', '102', 'Seller', 0.02, store1)

    # 管理员输入汽车信息
    print("管理员开始录入汽车信息：")
    manager1.input_car(store1)
    print(store1)

    # 选择并销售汽车
    car_index = 1  # 选择第二辆车
    if 0 <= car_index < len(store1.cars):
        car1 = store1.cars[car_index]
        print(car1)
        manager1.set_price(car1, 100)  # 设置价格为100元
        print(car1)
        store1.sell_car(car_index, seller1)  # 销售员小张销售该车
    else:
        print("无效的汽车索引！")

    car_index = 2  # 选择第三辆车
    if 0 <= car_index < len(store1.cars):
        car2 = store1.cars[car_index]
        print(car2)
        store1.sell_car(car_index, seller1)  # 销售员小张销售该车
    else:
        print("无效的汽车索引！")

    print('销售员{}当月佣金总共{}元。'.format(seller1.name, seller1.commission))

    car_index = 0  # 选择第一辆车
    if 0 <= car_index < len(store1.cars):
        car3 = store1.cars[car_index]
        store1.sell_car(car_index, seller2)  # 销售员小明销售该车
    else:
        print("无效的汽车索引！")

    print('销售员{}当月佣金总共{}元。'.format(seller2.name, seller2.commission))

    print(store1)