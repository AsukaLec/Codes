import pandas as pd
from pathlib import Path

# file_in = Path('机器学习作业/大作业/data/heart_data.csv')
# file_out = file_in.with_name('heart_data_clean.csv')

# df = pd.read_csv(file_in).drop(columns=['index', 'id'])

# 血压范围
# df = df[(df['ap_hi'] > 0) & (df['ap_hi'] <= 250) &
#         (df['ap_lo'] > 0) & (df['ap_lo'] <= 250)]

# BMI过滤
# df['bmi'] = df['weight'] / (df['height'] / 100) ** 2
# df = df[df['bmi'] <= 100]        # 删极端 BMI
# df = df[df['bmi'] >= 9]  


# df.drop(columns=['bmi']).to_csv(file_out, index=False)

# print(f' cleaned → {file_out}  样本数: {len(df)}')


in_file = Path('机器学习作业/大作业/data/heart_data_clean.csv')
out_file = in_file.with_name('heart_data_clean.csv')

df = pd.read_csv(in_file)

# 血压极限区间
df = df[(df['ap_hi'] >= 20) & (df['ap_hi'] <= 250) &
        (df['ap_lo'] >= 15) & (df['ap_lo'] <= 200)]

after = len(df)
print(f'剩余 {after} 条')
df.to_csv(out_file, index=False)






