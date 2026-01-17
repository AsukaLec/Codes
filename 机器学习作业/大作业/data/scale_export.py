# scale_export_with_label.py
import pandas as pd
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import StandardScaler, OneHotEncoder
from pathlib import Path

# 1. 读取清洗后数据
df = pd.read_csv('机器学习作业/大作业/data/heart_data_clean.csv')

# 2. 列分类
cont_cols = ['age', 'height', 'weight', 'ap_hi', 'ap_lo']
ord_cols = ['gluc', 'cholesterol']
bin_cols = ['smoke', 'alco', 'active']
cat_cols = ['gender']

# 3. 预处理三段式（只变换特征，不碰标签）
preprocessor = ColumnTransformer(
    [('num', StandardScaler(), cont_cols + ord_cols),
     ('bin', 'passthrough', bin_cols),
     ('cat', OneHotEncoder(drop='if_binary'), cat_cols)],
    remainder='drop')

# 4. fit + transform
X_scaled = preprocessor.fit_transform(df.drop(columns=['cardio']))
y = df['cardio'].values                                     # 取出标签

# 5. 友好列名
num_names = preprocessor.named_transformers_['num'].get_feature_names_out(cont_cols + ord_cols).tolist()
bin_names = bin_cols
cat_names = preprocessor.named_transformers_['cat'].get_feature_names_out(cat_cols).tolist()
feat_names = num_names + bin_names + cat_names

# 6. 拼成 DataFrame 并保存
out_dir = Path('机器学习作业/大作业/data')
out_dir.mkdir(exist_ok=True)

out_df = pd.DataFrame(X_scaled, columns=feat_names)
out_df['cardio'] = y                 # 标签放最后
out_df.to_csv(out_dir / 'X_scaled_with_label.csv', index=False)

print('Saved → visual/X_scaled_with_label.csv')
print('形状:', out_df.shape)
