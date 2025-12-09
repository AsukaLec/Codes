import numpy as np
import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import RandomizedSearchCV
import time
start = time.time()


# 加载数据
train_data = pd.read_csv("./py/pyai/train.csv")
test_data = pd.read_csv("./py/pyai/test.csv")

# 准备标签和特征
y = train_data["Survived"]
features = ["Pclass", "Sex", "SibSp", "Parch"]
X = pd.get_dummies(train_data[features])
X_test = pd.get_dummies(test_data[features])

# 定义参数分布
param_dist = {
    'n_estimators': [100, 200, 300, 400, 500],
    'max_depth': [5, 10, 15, 20, None],
    'min_samples_split': [2, 5, 10],
    'min_samples_leaf': [1, 2, 4],
    'max_features': ['auto', 'sqrt', 'log2']
}

# 初始化随机森林模型
model = RandomForestClassifier(random_state=1)

# 初始化随机搜索
random_search = RandomizedSearchCV(model, param_distributions=param_dist, n_iter=100, cv=5, scoring='accuracy', n_jobs=-1, random_state=1)

# 执行随机搜索
random_search.fit(X, y)

# 输出最佳参数
print("Best parameters:", random_search.best_params_)

# 使用最佳参数训练模型
best_model = random_search.best_estimator_
best_model.fit(X, y)

# 进行预测
predictions = best_model.predict(X_test)

# 准备提交结果
output = pd.DataFrame({'PassengerId': test_data.PassengerId, 'Survived': predictions})
output.to_csv('./py/pyai/submission2.csv', index=False)
print("Your submission was successfully saved!")

end = time.time()
print('Running time: %s Seconds'%(end-start))
