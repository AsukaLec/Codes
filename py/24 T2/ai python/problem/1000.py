ori = input()
pos = ori.find(' ')
str1 = ori[0:pos]
str2 = ori[pos+1:]
ans = int(str1) + int (str2)
print(ans)