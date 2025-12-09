import pandas as pd

def get_columns_as_list(df):
    """
    返回 DataFrame 的列名列表。
    
    参数:
    df (pd.DataFrame): 输入的 DataFrame
    
    返回:
    list: DataFrame 列名的列表
    """
    return df.columns.tolist()

# 示例使用
# 假设您有一个 DataFrame
data = {
    'A': [1, 2, 3],
    'B': [4, 5, 6],
    'C': [7, 8, 9]
}
df = pd.DataFrame(data)

# 调用函数并打印结果
columns_list = get_columns_as_list(df)

print(columns_list)  # 输出: Index(['A', 'B', 'C'], dtype='object')
