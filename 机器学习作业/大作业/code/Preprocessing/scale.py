# scale_final.py
import pandas as pd
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import StandardScaler, OneHotEncoder
from pathlib import Path

df = pd.read_csv('机器学习作业/大作业/data/heart_data_featured.csv')

cont_cols = ['age', 'height', 'weight', 'ap_hi', 'ap_lo']
ord_cols = ['gluc', 'cholesterol']
bin_cols = ['smoke', 'alco', 'active']
cat_cols = ['gender']
manual_cols = ['BMI', 'PP', 'MAR', 'WPC', 'GPB', 'ABP', 'RISK', 'AG', 'CBMI', 'PPA']

preprocessor = ColumnTransformer(
    [('num', StandardScaler(), cont_cols + ord_cols + manual_cols),
     ('bin', 'passthrough', bin_cols),
     ('cat', OneHotEncoder(drop='if_binary'), cat_cols)],
    remainder='drop')

# fit
X_scaled = preprocessor.fit_transform(df.drop(columns=['cardio']))
y = df['cardio'].values

num_names = preprocessor.named_transformers_['num'].get_feature_names_out(cont_cols + ord_cols + manual_cols).tolist()
bin_names = bin_cols
cat_names = preprocessor.named_transformers_['cat'].get_feature_names_out(cat_cols).tolist()
feat_names = num_names + bin_names + cat_names


out_dir = Path('机器学习作业/大作业/data')
out_df = pd.DataFrame(X_scaled, columns=feat_names)
out_df['cardio'] = y
out_df.to_csv(out_dir / 'heart_data_scaled.csv', index=False)


