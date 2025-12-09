# import sys
# # from PyQt5.QtWidgets import (QApplication, QMainWindow, QTextEdit,
# #                             QAction, QFileDialog, QMessageBox)
# from PyQt5.Qt import *

# class Notepad(QMainWindow):
#     def __init__(self):
#         super().__init__()
#         self.initUI()
       
#     def initUI(self):
#         self.text_edit = QTextEdit(self)
#         self.setCentralWidget(self.text_edit)
       
#         self.create_actions()
#         self.create_menus()
       
#         self.setWindowTitle('简易记事本')
#         self.setGeometry(100, 100, 800, 600)
       
#     def create_actions(self):
#         # 文件菜单动作
#         self.new_action = QAction('新建', self)
#         self.new_action.setShortcut('Ctrl+N')
#         self.new_action.triggered.connect(self.new_file)
       
#         self.open_action = QAction('打开', self)
#         self.open_action.setShortcut('Ctrl+O')
#         self.open_action.triggered.connect(self.open_file)
       
#         self.save_action = QAction('保存', self)
#         self.save_action.setShortcut('Ctrl+S')
#         self.save_action.triggered.connect(self.save_file)
       
#         self.exit_action = QAction('退出', self)
#         self.exit_action.setShortcut('Ctrl+Q')
#         self.exit_action.triggered.connect(self.close)
       
#         # 编辑菜单动作
#         self.copy_action = QAction('复制', self)
#         self.copy_action.setShortcut('Ctrl+C')
#         self.copy_action.triggered.connect(self.text_edit.copy)
       
#         self.paste_action = QAction('粘贴', self)
#         self.paste_action.setShortcut('Ctrl+V')
#         self.paste_action.triggered.connect(self.text_edit.paste)
       
#         self.cut_action = QAction('剪切', self)
#         self.cut_action.setShortcut('Ctrl+X')
#         self.cut_action.triggered.connect(self.text_edit.cut)
       
#     def create_menus(self):
#         menubar = self.menuBar()
       
#         # 文件菜单
#         file_menu = menubar.addMenu('文件')
#         file_menu.addAction(self.new_action)
#         file_menu.addAction(self.open_action)
#         file_menu.addAction(self.save_action)
#         file_menu.addSeparator()
#         file_menu.addAction(self.exit_action)
       
#         # 编辑菜单
#         edit_menu = menubar.addMenu('编辑')
#         edit_menu.addAction(self.copy_action)
#         edit_menu.addAction(self.paste_action)
#         edit_menu.addAction(self.cut_action)
       
#     def new_file(self):
#         self.text_edit.clear()
       
#     def open_file(self):
#         filename, _ = QFileDialog.getOpenFileName(self, '打开文件')
#         if filename:
#             try:
#                 with open(filename, 'r') as f:
#                     self.text_edit.setText(f.read())
#             except Exception as e:
#                 QMessageBox.warning(self, '错误', f'无法打开文件: {e}')
               
#     def save_file(self):
#         filename, _ = QFileDialog.getSaveFileName(self, '保存文件')
#         if filename:
#             try:
#                 with open(filename, 'w') as f:
#                     f.write(self.text_edit.toPlainText())
#             except Exception as e:
#                 QMessageBox.warning(self, '错误', f'无法保存文件: {e}')

# if __name__ == '__main__':
#     app = QApplication(sys.argv)
#     notepad = Notepad()
#     notepad.show()
#     sys.exit(app.exec_())





# import pysat.formula
# from pysat.solvers import Minisat22
# import time

# cnf = pysat.formula.CNF()

# cnf.append([])
# ##求解器解决cnf问题
# # 使用 Minisat22 解决器
# solver = Minisat22()

# # 逐个添加子句
# for clause in cnf.clauses:
#     solver.add_clause(clause)



# if solver.solve():
#     print ("yes")
# else:
#     print("无解")



# import itertools

# def generate_combinations(lst):
#     # 生成所有三个元素的组合
#     combinations = list(itertools.combinations(lst, 3))
#     return combinations

# # 示例用法
# lst = [1, 2, 3, 4, 5]
# combinations = generate_combinations(lst)


# for j in combinations:

#     j = str(j)
#     length = len(j)
#     j = j[1: length - 2]
#     print(j)


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
                cycle = []
                node = current_node
                while node is not None:
                    cycle.append(node)
                    node = parent[node]
                cycle.append(neighbor)  # 添加环的起始节点
                del cycle[len(cycle) - 1]
                return cycle[::-1]  # 反转列表以从起始节点开始
    
    return None  # 没有找到环

# 示例用法
edges = [107, 104, 207, 203, 305, 506, 406]
cycle = find_cycle(edges)
if cycle:
    print("环的遍历顺序:", cycle)
else:
    print("没有找到环")
