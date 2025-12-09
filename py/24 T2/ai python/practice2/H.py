########## Begin ########
#函数is_prime，判断输入参数n是否素数，是则return True，否则False
########## End ########## 
def is_prime(n):
    t = 2
    p = 0
    while (n>t):
        if n%t ==0:
            p+=1
        t+=1
    if p==0:
        return True
    else:
        return False


########## Begin ########
#函数palindromic 接收一个数字为参数，判定其是否为回文数，返回布尔值，是则return True，否则False
########## End ########## 
def palindromic(n):
    num_str=str(n)
    return num_str == num_str[::-1]
            
########## Begin ########
#函数reverse_num 接收一个整数，返回其逆序字符串对应的整数 
########## End ##########
def reverse_num(n):
    num_str=str(n)
    return int(num_str[::-1])

# 获取number个反素数
def reverse_prime(number):
    i = 2
    count = 0
    while True:
        if not palindromic(i) and is_prime(i) and is_prime(reverse_num(i)):
            print(i, end=' ')  # i为回文素数时输出i，输出后不换行
            count = count + 1
            if count == number:
                break
        i = i + 1


if __name__ == "__main__":
    n = int(input())
    reverse_prime(n) 