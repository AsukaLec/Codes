import pandas as pd 
import seaborn as sns
from sklearn.preprocessing import LabelEncoder
from sklearn.tree import DecisionTreeRegressor
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_log_error
import joblib
import numpy as np
import json

# from mainprogress import history_file_path, prediction_file_path, save_file_path, generate_mode

# history_file_path = './data_set/train.csv'
# prediction_file_path = './data_set/test.csv'
# save_file_path = './submissionv1.csv'
# generate_mode = 'global'
# generate_mode = 'recent'


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


def generate_prediction():
    train = pd.read_csv(history_file_path)

    # 从日期列提取星期几和月份中的天数
    train['date'] = pd.to_datetime(train['date'])
    train['dayweek'] = train['date'].dt.day_of_week
    train['daymonth'] = train['date'].dt.day
    train.rename(columns={'store_nbr':'store'}, inplace=True)

    # 对family列进行标签编码
    family_encoder = LabelEncoder()
    train['family'] = family_encoder.fit_transform(train['family'])

    # 保存编码器，以便以后使用
    joblib.dump(family_encoder, 'family_encoder.pkl')

    # 由于我们的任务是预测所有商店和家庭在未来15天的销售情况，因此让我们的模型从最近的数据中学习关系可能会有所帮助
    # 训练数据集包括过去4年的数据，所以我们只选择过去6个月的数据来训练我们的模型
    if generate_method =='global':
        train = train
    if generate_method == 'recent':
        # 获取最新日期
        latest_date = train['date'].max()
        # 计算六个月前的日期
        six_months_before = latest_date - pd.DateOffset(months=6)
        # 筛选出六个月内的数据
        train = train[train['date'] > six_months_before]

    # 我们的特征将只有storenbr、family、dayweek和daymonth
    # 因此我们所有的数据点都将位于一个四维空间中
    X = train.drop(columns=['id', 'date', 'sales'])
    y = train[['sales']]

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3)


    # 使用CART算法，该模型将学习如下关系："对于storenbr=1、family=AUTOMOTIVE、dayweek=星期天、daymonth=1日，预测销售量=3000"
    cart = DecisionTreeRegressor()
    cart.fit(X_train, y_train)

    preds = cart.predict(X_test)

    # 计算我们模型的RMSLE
    np.sqrt(mean_squared_log_error(preds, y_test))

    # 预处理测试数据，以便我们的模型进行预测
    test = pd.read_csv(prediction_file_path)

    ids = test['id']
    test['family'] = family_encoder.transform(test['family'])
    test['date'] = pd.to_datetime(test['date'])
    test['dayweek'] = test['date'].dt.day_of_week
    test['daymonth'] = test['date'].dt.day

    test.rename(columns={'store_nbr':'store'}, inplace=True)

    test.drop(columns=['date', 'id'], inplace=True)

    # 让我们的模型预测测试数据的销售情况
    test_preds = cart.predict(test)

    # 将我们对测试数据的预测转换为csv，以便提交

    final_predictions = pd.DataFrame({'sales':test_preds})
    final_predictions['id'] = ids
    final_predictions = final_predictions[['id', 'sales']]

    final_predictions.to_csv(save_file_path, index=False)
    final_predictions.to_csv('./tmep/1.csv', index=False)

    df2 = pd.read_csv(prediction_file_path)
    df3 = pd.read_csv('./tmep/1.csv')

    df23 = pd.merge(df2, df3, on='id', how='outer')

    df23.to_csv('./tmep/2.csv', index= False)


def main():
    generate_prediction()

if __name__ == '__main__':
    main()

