import pysat.formula
from pysat.solvers import Minisat22
import time


# 创建一个新的 CNF（Conjunctive Normal Form）公式
cnf = pysat.formula.CNF()

offset = int(10000) # 偏移量 区别 边集 和 哈密顿图的边集

x = int(input("请输入边的个数:"))
dots = int(input("请输入结点的总数：")) #输入最大节点数，减少内存占用
dots += 1
print("请输入(一行一个数)相连的边:")

not_list = []
while x:
    a = int(input())
    b = int(input())
    if a > b :
        t = a
        a = b
        b = t
    cnf.append([a * 100 + b + offset])
    cnf.append([- (b * 100 + a + offset)])
    not_list.append(a * 100 + b + offset)
    not_list.append(b * 100 + a + offset)
    x -= 1

for i in range(10100, offset + (dots - 1) * 101) :
    if i not in not_list:
        cnf.append([-i])
# 构造命题逻辑公式

# 原来的图中的每一个结点都会在哈密顿图中
for b in range(1, dots):
    list0 = []
    for i in range(1, dots):
        list0.append(i * 100 + b + offset)
    cnf.append(list0)

for a in range(1, dots):
    list0 = []
    for i in range(1, dots):
        list0.append(a * 100 + i + offset)
    cnf.append(list0)

# #每个结点在哈密顿图中仅出现一次
# for b in range (1, dots):
#     for i in range (1, dots):
#         for j in range (1, dots):
#             list1 = [-(offset + i * 100 + b ), -(offset + j * 100 + b)]
#             cnf.append(list1)




# 使用 Minisat22 解决器
solver = Minisat22()

# 逐个添加子句
for clause in cnf.clauses:
    solver.add_clause(clause)

start =time.time()
# 检查 SAT 问题是否有解
if solver.solve():
    model = solver.get_model()  # 获取模型，即满足条件的变量取值
    ans = [1]
    
    times = dots - 2

    index0 = int(1)

    while times :
        for i in range (offset + index0 * 100, offset + index0 * 100 + dots - 1 ):
            t = str(i + 1)
            if model[i] > 0 and int(t[3:]) not in ans:
                print(model[i])
                
                ans.append(int(t[3:]))
                index0 = int(t[3:])
                break
        times -= 1

    print(cnf.clauses)
    print("here is a ~~~")
    print(model[10100:])
    print(ans)
    
else:
    print("无解")


end = time.time()

print('Running time: %s Seconds'%(end-start))
