absencenum = int(input())#缺席学生的索引（从1开始）
studentname = []
inputlist = input()
for i in inputlist.split(','):
   result = i
   studentname.append(result)
count = 0
# 请在此添加代码，填入循环遍历studentname列表的代码
########## Begin ##########

for student in studentname:
########## End ##########
    count += 1
    # 请在此添加代码，跳过缺席学生
    ########## Begin ##########
    if count == absencenum:
        continue
    ########## End ##########
    print(student, "的试卷已阅")