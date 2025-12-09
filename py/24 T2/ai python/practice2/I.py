#输出**月有多少天

########## Begin ########
#函数is_leap：输入参数year，判断是闰年或平年，返回True或False
########## End ########## 
def is_leap(year):
    if (year%4==0 and year%100!=0) or year%400==0:
        return True
    else:
        return False
########## Begin ########
#函数days_of_month：输入参数年月字符串（如200101），返回对应月份的天数（31）
########## End ##########  
def days_of_month(num_str):
    year = int(num_str[0:4])
    month = int (num_str[4:6])

    biglist = [1,3,5,7,8,10,12]
    smalllist = [4,6,9,11]

    if is_leap(year):
        if month in biglist:
            return 31
        elif month in smalllist:
            return 30
        else: return 29
    else:
        if month in biglist:
            return 31
        elif month in smalllist:
            return 30
        else: return 28



if __name__ == '__main__':
    date_in = input()  # 输入一个年月
    print(days_of_month(date_in)) 