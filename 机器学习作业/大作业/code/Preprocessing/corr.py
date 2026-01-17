import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from pathlib import Path
plt.rcParams['font.sans-serif'] = ['SimHei']     
plt.rcParams['axes.unicode_minus'] = False

df = pd.read_csv('data/heart_data_featured.csv')
out_dir = Path('image/')
out_dir.mkdir(exist_ok=True)

corr = df.corr()

plt.figure(figsize=(16, 14))
sns.heatmap(corr, annot=True, fmt='.2f', cmap='coolwarm',
            square=True, linewidths=.5, cbar_kws={"shrink": .8})
plt.title('皮尔逊相关性热力图', fontsize=16)
plt.tight_layout()
plt.savefig(out_dir / 'corr_heatmap.png', dpi=500)
plt.close()


