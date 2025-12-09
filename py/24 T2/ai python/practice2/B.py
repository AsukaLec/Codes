workYear = int(input())

if workYear < 5:
    print("工资涨幅为0")

elif workYear >= 5 and workYear < 10:
    print("工资涨幅为5%")

elif workYear >= 10 and workYear < 15:
    print("工资涨幅为10%")

else :
    print("工资涨幅为15%")