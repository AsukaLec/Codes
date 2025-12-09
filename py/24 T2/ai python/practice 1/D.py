fee = int(input())
live = float(input())
fee *= 17
live *= 5
sum = (fee + live)*0.6
print("本学期你能够贷款{:.2f}元".format(sum))
