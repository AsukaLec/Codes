import pandas as pd
from pathlib import Path

n_components = 6

orig_file = Path('机器学习作业/大作业/data/heart_data_scaled.csv')   
orig_df = pd.read_csv(orig_file)
orig_df = orig_df.drop(columns=['cardio'])

pca_file = Path(f'机器学习作业/大作业/data/X_pca_{n_components}d_pure.csv' )  
pca_df = pd.read_csv(pca_file)
  
merged_df = pd.concat([orig_df, pca_df], axis=1)  


out_file = orig_file.with_name('heart_data_pca.csv')
merged_df.to_csv(out_file, index=False)

