import numpy as np
import pandas as pd
import time
from joblib import dump, load

start = time.time()

train_data = pd.read_csv("./py/pyai/train.csv")
test_data = pd.read_csv("./py/pyai/test.csv")


from sklearn.ensemble import RandomForestClassifier

y = train_data["Survived"]

features = ["Pclass", "Sex", "SibSp", "Parch"]
X = pd.get_dummies(train_data[features])
X_test = pd.get_dummies(test_data[features])

model = RandomForestClassifier(n_estimators=100, max_depth=5, random_state=1)
model.fit(X, y)

dump(model, './py/pyai/random_forest_model.joblib')

predictions = model.predict(X_test)

output = pd.DataFrame({'PassengerId': test_data.PassengerId, 'Survived': predictions})
output.to_csv('./py/pyai/submission.csv', index=False)
print("Your submission was successfully saved!")

end = time.time()
print('Running time: %s Seconds'%(end-start))
