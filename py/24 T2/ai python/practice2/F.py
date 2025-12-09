########## Begin ########## 
#定义self_divisor函数。
#当该数为自除数，返回值为True

########## End ########## 
def self_divisor(num):
    num_str=str(num)
    length = len(num_str)
    n = 0
    for i in range(0,length):
        k=(int(num_str[i]))
        if k == 0:
            return False
            break
        if num%k==0:
            n+=1
    if n == length :
        return True
    else :
        return False


def output(n):
    """输出不小于n的自除数，无返回值"""
    for num in range(1, n + 1):  # 注意不大于包括等于n
        if self_divisor(num):  # 调用函数，当返回值为True时，该数为自除数，输出这个数
            print(num, end=' ')  # 输出以空格结尾


if __name__ == '__main__':
    m = int(input())
    output(m)

