import random
import itertools


def generate_hamiltonian_graph(n):
    """
    生成一个包含哈密顿环的图。
    :param n: 节点数
    :return: 边的列表
    """
    # 生成一个环
    edges = [(i, (i % n) + 1) for i in range(1, n)]
    # 随机添加一些额外的边
    for _ in range(n // 2):
        a, b = random.sample(range(1, n + 1), 2)
        if (a, b) not in edges and (b, a) not in edges:
            edges.append((a, b))
    return edges


def write_input_file(file_name, edges):
    """
    将图数据写入文件。
    :param file_name: 文件名
    :param edges: 边的列表
    """
    with open(file_name, 'w', encoding='utf-8') as file:
        file.write(f"{len(edges)}\n")
        file.write(f"{len(set(itertools.chain(*edges)))}\n")
        for edge in edges:
            file.write(f"{edge[0]} {edge[1]}\n")
        file.write("yes\n")


def main():
    num_files = 1
    max_nodes = 199
    base_path = "./py/Hamiton_relate/in"
    
    for i in range(1, num_files + 1):
        n = random.randint(100, max_nodes)  # 节点数至少为3，最多为99
        edges = generate_hamiltonian_graph(n)
        
        file_name = f"{base_path}{i}.txt"
        write_input_file(file_name, edges)
        print(f"Generated {file_name} with Hamiltonian cycle")


if __name__ == "__main__":
    main()


