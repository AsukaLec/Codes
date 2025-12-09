import pandas as pd 
import seaborn as sns
sns.set_palette('Set2')
sns.set_style('whitegrid')
from sklearn.preprocessing import LabelEncoder
from sklearn.tree import DecisionTreeRegressor
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_log_error
import joblib
import numpy as np
import time 

start = time.time()

train = pd.read_csv('E:/桌面/price_estimate/data_set/merged_data.csv')

# 从日期列提取星期几和月份中的天数
train['date'] = pd.to_datetime(train['date'])
train['dayweek'] = train['date'].dt.day_of_week
train['daymonth'] = train['date'].dt.day
train.rename(columns={'store_nbr':'store'}, inplace=True)

sub = train

# 对family列进行标签编码
family_encoder = LabelEncoder()
train['family'] = family_encoder.fit_transform(train['family'])

# 保存编码器，以便以后使用
joblib.dump(family_encoder, 'family_encoder.pkl')

# 由于我们的任务是预测所有商店和家庭在未来15天的销售情况，因此让我们的模型从最近的数据中学习关系可能会有所帮助
# 训练数据集包括过去4年的数据，所以我们只选择过去6个月的数据来训练我们的模型
# past6mon = train.query('date > "2017-01"')
past6mon = train

# 我们的特征将只有storenbr、family、dayweek和daymonth
# 因此我们所有的数据点都将位于一个四维空间中
X = past6mon.drop(columns=['id', 'date', 'sales'])
y = past6mon[['sales']]

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3)


# 使用CART算法，该模型将学习如下关系："对于storenbr=1、family=AUTOMOTIVE、dayweek=星期天、daymonth=1日，预测销售量=3000"
cart = DecisionTreeRegressor()
cart.fit(X_train, y_train)

preds = cart.predict(X_test)

# 计算我们模型的RMSLE
np.sqrt(mean_squared_log_error(preds, y_test))


# 预处理测试数据，以便我们的模型进行预测
test = pd.read_csv('./data_set/merged_data1.csv')

ids = test['id']
test['family'] = family_encoder.transform(test['family'])
test['date'] = pd.to_datetime(test['date'])
test['dayweek'] = test['date'].dt.day_of_week
test['daymonth'] = test['date'].dt.day


test.rename(columns={'store_nbr':'store'}, inplace=True)

test.drop(columns=['date', 'id'], inplace=True)

# 让我们的模型预测测试数据的销售情况
test_preds = cart.predict(test)

# 将我们对测试数据的预测转换为csv，以便提交到比赛中
final_predictions = pd.DataFrame({'sales':test_preds})
final_predictions['id'] = ids
final_predictions = final_predictions[['id', 'sales']]

final_predictions.to_csv('submissionv1.csv', index=False)

end = time.time()
print('运行时间：%s 秒'%(end-start))






# 绘制销售趋势图
sns.relplot(data=sub, kind='line', x='date', y='sales', height=5, aspect=5)

# 绘制不同星期几的销售散点图
sns.relplot(data=sub, kind='scatter', x='date', y='sales', hue='dayweek', height=5, aspect=5, palette='Set2')

# 验证周六和周日的中位数销售量是否确实高于其他日子
median_sales = sub.groupby('dayweek')['sales'].median()
median_sales = median_sales.reset_index()
sns.catplot(data=median_sales, kind='bar', x='dayweek', y='sales')

# 让我们也检查一下月份中的天数是否是一个好的预测变量
dm = sub.groupby('daymonth')['sales'].median()
dm = dm.reset_index()
dm.head()

# 绘制每个月份中位数销售量的柱状图
sns.catplot(data=dm, kind='bar', x='daymonth', y='sales', height=5, aspect=2)
