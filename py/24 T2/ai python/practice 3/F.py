import string

########## Begin ########
def found(m):
    # 检查m是否只包含小写字母
    if not set(m).issubset(string.ascii_lowercase):
        return 'ERROR'
    
    # 输入字符串n
    n = input()
    
    # 检查m中的每个字符是否都在n中出现
    for char in m:
        if char not in n:
            return 'NOT FOUND'
    
    return 'FOUND'
########## End ##########   

if __name__ == '__main__':
    m = input()
    output = found(m)
    print(output)