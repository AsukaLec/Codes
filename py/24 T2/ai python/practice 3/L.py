num = input() 
hole_dic = {'0':1, '1':0, '2':0, '3':0, '4':1, '5':0, '6':1, '7':0, '8':2, '9':1}
########## Begin ########## 
count_of_hole = 0
for i in num:
    count_of_hole += hole_dic[i]
########## End ########## 

print(count_of_hole)  