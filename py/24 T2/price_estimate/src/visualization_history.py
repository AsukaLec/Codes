import pandas as pd
import matplotlib.pyplot as plt
import json


def set_path_and_method():
    global history_file_path
    global prediction_file_path
    global save_file_path
    global generate_method
    global file_path
    global data
    with open("params.json", "r") as f:
        params = json.load(f)
    history_file_path = params["history_file_path"]
    prediction_file_path = params["prediction_file_path"]
    save_file_path = params["save_file_path"]
    generate_method = params["generate_method"]

    file_path = history_file_path  
    data = pd.read_csv(file_path)


def generate_pic ():
    set_path_and_method()
    # 转换日期格式
    data['date'] = pd.to_datetime(data['date'])

    # 按日期统计总销售额
    daily_sales = data.groupby('date')['sales'].sum().reset_index()

    # 按商品类别（family）统计销售额
    category_sales = data.groupby('family')['sales'].sum().reset_index()

    # 设置绘图风格
    plt.style.use('ggplot')

    # 创建一个图形窗口
    plt.figure(figsize=(14, 10))

    # 第一个子图：按日期统计销售额的折线图
    plt.subplot(1, 2, 1)
    plt.plot(daily_sales['date'], daily_sales['sales'], marker='o', color='tab:blue')
    plt.title('Daily Sales', fontsize=14)
    plt.xlabel('Date', fontsize=12)
    plt.ylabel('Sales', fontsize=12)
    plt.xticks(rotation=45)
    plt.grid(True)

    # 第二个子图：按商品类别统计销售额的柱状图
    plt.subplot(1, 2, 2)
    plt.bar(category_sales['family'], category_sales['sales'], color='tab:orange')
    plt.title('Sales by Product Category', fontsize=14)
    plt.xlabel('Product Category', fontsize=12)
    plt.ylabel('Sales', fontsize=12)
    plt.xticks(rotation=90)
    plt.grid(True)

    # 调整布局
    plt.tight_layout()

    # 显示图形
    plt.show()

def main():
    generate_pic()
    
if __name__ == '__main__':
    main()

