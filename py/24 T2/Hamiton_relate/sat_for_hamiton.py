import pysat.formula
from pysat.solvers import Minisat22
import time
import copy
import itertools

file_in = open('./py/Hamiton_relate/in.txt', 'r')
file_out = open('./py/Hamiton_relate/out.txt', 'w')

# 创建一个新的 CNF（Conjunctive Normal Form）公式
cnf = pysat.formula.CNF()
#offset = int(0) # 偏移量 区别 边集 和 哈密顿图的边集

## 初始化
x = int(file_in.readline())
dots = int(file_in.readline()) #输入最大节点数，减少内存占用
dots += 1

not_list = []
list_ans = []
list_for_step2 = []

while x:
    a, b = map(int, file_in.readline().split())

    if a > b :
        t = a
        a = b
        b = t
    cnf.append([-(b * 100 + a)]) # 防止重复 第一位永远比第二位小
    
    list_ans.append(a * 100 + b)
    list_for_step2.append(a * 100 + b)

    not_list.append(a * 100 + b )
    not_list.append(b * 100 + a )    
    x -= 1

list_for_step2.sort()

file_in.close()

print(list_for_step2) #维护用
print()



##命题逻辑公式的构建和输入
#(e_ij 不存在时 强制设为假 )
for i in range(100, (dots - 1) * 101) :
    if i not in not_list:
        cnf.append([-i])

#at-least-two
for i in range(1, dots):
    new_list = []
    for k in range (len(list_for_step2)):
        if int(list_for_step2[k] // 100 ) == i or int(list_for_step2[k]) % 100 == i:
            new_list.append(list_for_step2[k])

    if len(new_list) == 2:
        cnf.append([new_list[0]])
        cnf.append([new_list[1]])
    else:
        for j in range(len(new_list)):
            target_list= copy.deepcopy(new_list)
            del target_list[j]
            cnf.append(target_list)

#at-most-two
for i in range (1, dots):
    new_list = []
    for k in range (len(list_for_step2)):
        if int(list_for_step2[k] // 100 ) == i or int(list_for_step2[k]) % 100 == i:
            new_list.append(list_for_step2[k])
    
    if len(new_list) > 2:
        target_list = [-x for x in new_list]
        combinations = list(itertools.combinations(target_list, 3))

        for combo in combinations:
            target = list(combo)
            cnf.append(target)



##求解器解决cnf问题
# 使用 Minisat22 解决器
solver = Minisat22()

# 逐个添加子句
for clause in cnf.clauses:
    solver.add_clause(clause)

 #print(cnf.clauses)维护用


#对于已知的在哈密顿图中的边 用于输出环
def parse_edge(edge):
    # 解析三位数的边
    return (edge // 100, edge % 100)

def find_cycle(edges):
    # 构建邻接表
    adjacency_list = {}
    for edge in edges:
        node1, node2 = parse_edge(edge)
        if node1 not in adjacency_list:
            adjacency_list[node1] = []
        if node2 not in adjacency_list:
            adjacency_list[node2] = []
        adjacency_list[node1].append(node2)
        adjacency_list[node2].append(node1)
    
    # 从节点1开始寻找环
    start_node = 1
    visited = set()
    parent = {start_node: None}
    stack = [start_node]
    
    while stack:
        current_node = stack.pop()
        visited.add(current_node)
        
        for neighbor in adjacency_list[current_node]:
            if neighbor not in visited:
                stack.append(neighbor)
                parent[neighbor] = current_node
            elif neighbor in visited and neighbor != parent[current_node]:
                # 找到环
                cycle = [1]
                node = current_node
                while node is not None:
                    cycle.append(node)
                    node = parent[node]
                cycle.append(neighbor)  # 添加环的起始节点
                del cycle[len(cycle) - 2:]
                return cycle  # 反转列表以从起始节点开始
    
    return None  # 没有找到环


start =time.time()
# 检查 SAT 问题是否有解
if solver.solve():
    model = solver.get_model()  # 获取模型，即满足条件的变量取值
    ans = []
    for i in model[101:]:
        if i > 0 :
            ans.append(i)

    print(ans)# 维护用

    #输出环
    cycle = find_cycle(ans)
    file_out.write("The traversal order of the Haamiton diagram: " + str(cycle) + '\n')

else:
    file_out.write("No answer" + '\n')


end = time.time()

file_out.write('Running time: %s Seconds'%(end-start))

file_in.close()
file_out.close()
