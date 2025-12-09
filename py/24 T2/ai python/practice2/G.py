# 以下面程序中补充你的代码
########## Begin #######
#car_info函数，输入参数3个，输出参数1个（格式化字符串）
########## End ##########
def car_info(year,model,brand):
    return f"这是一辆{year}年生产，型号是{model}的{brand}牌汽车。"

# 以下内容不要修改
ls = input().split()  # 根据空格切分输入字符串为列表，列表元素可能是两个或三个
print(car_info(*ls))       # 调用函数，取列表中的全部数据做参数