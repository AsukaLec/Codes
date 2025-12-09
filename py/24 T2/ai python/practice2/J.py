import string
#string.ascii_lowercase即'abcdefghijklmnopqrstuvwxyz'

########## Begin ########
#函数found：输入参数m，判断是否'ERROR'，然后再调用input函数输入n字符串判断 'FOUND', 'NOT FOUND'，函数返回值为'ERROR'，'FOUND', 'NOT FOUND'。
def found(m):
    if m.isalpha() :
        n = input()
        for char in m:
            if char not in n:
                return 'NOT FOUND'
        return 'FOUND'
    else:
        return 'ERROR'

########## End ##########   
if __name__ == '__main__':
    m = input()
    output = found(m)
    print(output)