# import pandas as pd

# # 读取两个 CSV 文件
# prices_df = pd.read_csv('./data_set/oil.csv')
# sales_df = pd.read_csv('./data_set/test.csv')

# # 确保 date 列是 datetime 类型，以便正确合并
# prices_df['date'] = pd.to_datetime(prices_df['date'])
# sales_df['date'] = pd.to_datetime(sales_df['date'])

# # 合并两个 DataFrame，根据 date 列进行合并
# merged_df = pd.merge(sales_df, prices_df, on='date', how='left')

# # 保存合并后的 DataFrame 到新的 CSV 文件
# merged_df.to_csv('./data_set/merged_data1.csv', index=False)

# print("合并完成，已保存到 merged_data.csv")

import pandas as pd
import json

def set_path_and_method():
    global history_file_path
    global prediction_file_path
    global save_file_path
    global generate_method
    with open("params.json", "r") as f:
        params = json.load(f)
    history_file_path = params["history_file_path"]
    prediction_file_path = params["prediction_file_path"]
    save_file_path = params["save_file_path"]
    generate_method = params["generate_method"]

# 读取 CSV 文件
def merge_file():
    df1 = pd.read_csv(history_file_path)
    df2 = pd.read_csv(prediction_file_path)
    df3 = pd.read_csv(save_file_path)

    # 将第二个和第三个文件合并，使用 'id' 作为键
    df23 = pd.merge(df2, df3, on='id', how='outer')

    # 纵向合并两个 DataFrame
    df_combined = pd.concat([df1, df23], ignore_index=True)

    # 保存合并后的 DataFrame 到新的 CSV 文件
    df_combined.to_csv('./combined.csv', index=False)
    df_combined.to_csv(history_file_path, index=False)

def main():
    merge_file()

if __name__ == '__main__':
    main()


