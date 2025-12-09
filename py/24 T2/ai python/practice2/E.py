studentnum = int(input())
# 请在此添加代码，填入for循环遍历学生人数的代码
########## Begin ##########
 
########## End ##########
for student in range(1,studentnum+1):

    sum = 0
    inputlist = input()
	# 请在此添加代码，将输入转换成列表subjectscore
	########## Begin ##########
	 
	########## End ##########
    subjectscore = inputlist.split(',')
	# 请在此添加代码，填入for循环遍历学生分数的代码
	########## Begin ##########
	 
	########## End ##########
    for score in subjectscore:
	    score = int(score)
	    sum = sum + score
    print("第%d位同学的总分为:%d" %(student,sum))
 