# bp_2d_dot.py
import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

out_dir = Path('机器学习作业/大作业/data/visual/bp_plots')
out_dir.mkdir(exist_ok=True)

df = pd.read_csv('机器学习作业/大作业/data/heart_data_clean.csv', usecols=['ap_hi', 'ap_lo', 'cardio'])

plt.figure(figsize=(5, 5))
plt.scatter(df.query('cardio==0')['ap_hi'], df.query('cardio==0')['ap_lo'],
            c='skyblue', s=1, alpha=.3, label='no cardio')
plt.scatter(df.query('cardio==1')['ap_hi'], df.query('cardio==1')['ap_lo'],
            c='red', s=1, alpha=.8, label='cardio')
plt.xlabel('ap_hi'); plt.ylabel('ap_lo'); plt.legend()
plt.savefig(out_dir / 'bp_2d_vector.png', dpi=300)
