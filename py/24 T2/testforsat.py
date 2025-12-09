import pysat.formula
from pysat.solvers import Minisat22
import time
import copy
import itertools
import os

#控制程序读入
def read_input_file(file_name):
    """
    从指定文件读取输入数据。
    :param file_name: 输入文件的路径
    :return: 边的个数，结点总数，边的列表
    """
    with open(file_name, 'r', encoding='utf-8') as file:
        x = int(file.readline().strip())  # 边的个数
        dots = int(file.readline().strip()) + 1  # 结点总数
        edges = [tuple(map(int, line.strip().split())) for line in file]
    return x, dots, edges

#控制程序输出
def write_output_file(file_name, cycle, running_time):
    """
    将结果写入指定文件。
    :param file_name: 输出文件的路径
    :param cycle: 环的遍历顺序
    :param running_time: 运行时间
    """
    with open(file_name, 'w', encoding='utf-8') as file:
        if cycle:
            file.write("The traversal order of the Hamilton diagram: " + str(cycle) + '\n')
        else:
            file.write("No answer\n")
        file.write('Running time: %s Seconds\n' % running_time)

#格式化输入的边
def parse_edge(edge):
    return (edge // 100, edge % 100)

#sat求解器完成求解后，输出哈密顿图中的边，在此生成点的遍历顺序
def generate_cycle(edges):
    adjacency_list = {}
    for edge in edges:
        node1, node2 = parse_edge(edge)
        if node1 not in adjacency_list:
            adjacency_list[node1] = []
        if node2 not in adjacency_list:
            adjacency_list[node2] = []
        adjacency_list[node1].append(node2)
        adjacency_list[node2].append(node1)
    
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
                cycle = []
                node = current_node
                while node is not None:
                    cycle.append(node)
                    node = parent[node]
                cycle.append(neighbor)  # 添加环的起始节点
                del cycle[len(cycle) - 1]
                return cycle[::-1]  # 反转列表以从起始节点开始
    
    return None  # 没有找到环

#主函数，sat求解器进行求解
def main():
    """
    主函数，负责读取输入文件，构建CNF公式，调用求解器，并将结果写入输出文件。
    """
    input_file_name = './py/Hamiton_relate/in.txt'  # 输入文件路径
    output_file_name = './py/Hamiton_relate/out.txt'  # 输出文件路径
    
    # 从文件读取输入数据
    x, dots, edges = read_input_file(input_file_name)
    
    # 创建 CNF 公式
    cnf = pysat.formula.CNF()
    offset = 0  # 偏移量，区别边集和哈密顿图的边集
    not_list = []
    list_ans = []
    list_for_step2 = []
    
    for a, b in edges:
        if a > b:
            a, b = b, a
        cnf.append([-(b * 100 + a + offset)])  # 防止重复，第一位永远比第二位小
        list_ans.append(a * 100 + b)
        list_for_step2.append(a * 100 + b)
        not_list.append(a * 100 + b + offset)
        not_list.append(b * 100 + a + offset)
    
    list_for_step2.sort()
    
    # 命题逻辑公式的构建和输入
    # (e_ij 不存在时 强制设为假)
    for i in range(100, offset + (dots - 1) * 101):
        if i not in not_list:
            cnf.append([-i])
    
    # at-least-two
    for i in range(1, dots):
        new_list = []
        for k in range(len(list_for_step2)):
            if int(list_for_step2[k] / 100) == i or int(str(list_for_step2[k])[1:]) == i:
                new_list.append(list_for_step2[k])
        
        if len(new_list) == 2:
            cnf.append([new_list[0]])
            cnf.append([new_list[1]])
        else:
            for j in range(len(new_list)):
                target_list = copy.deepcopy(new_list)
                del target_list[j]
                cnf.append(target_list)
    
    # at-most-two
    for i in range(1, dots):
        new_list = []
        for k in range(len(list_for_step2)):
            if int(list_for_step2[k] / 100) == i or int(str(list_for_step2[k])[1:]) == i:
                new_list.append(list_for_step2[k])
        
        if len(new_list) > 2:
            target_list = [-x for x in new_list]
            combinations = list(itertools.combinations(target_list, 3))
            for combo in combinations:
                target = list(combo)
                cnf.append(target)
    
    # 使用 Minisat22 解决器
    solver = Minisat22()
    for clause in cnf.clauses:
        solver.add_clause(clause)
    
    start = time.time()
    if solver.solve():
        model = solver.get_model()  # 获取模型，即满足条件的变量取值
        ans = [i for i in model[101:] if i > 0]
        cycle = generate_cycle(ans)
    else:
        cycle = None
    end = time.time()
    
    # 写入输出文件
    write_output_file(output_file_name, cycle, end - start)


if __name__ == "__main__":
    main()
