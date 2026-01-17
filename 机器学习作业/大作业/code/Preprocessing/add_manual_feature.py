import pandas as pd
from pathlib import Path

file_in = Path('机器学习作业/大作业/data/heart_data_clean.csv')
df = pd.read_csv(file_in)
file = file_in.with_name('heart_data_featured.csv')

df['BMI'] = df['weight'] / (df['height'] / 100) ** 2
df['PP'] = df['ap_hi'] - df['ap_lo']
df['MAR'] = (df['ap_hi'] + 2 * df['ap_lo']) / 3
df['WPC'] = df['weight'] / df['height']
df['GPB'] = df['gluc'] * df['BMI']
df['ABP'] = df['age'] * (df['ap_hi'] / 100)
df['RISK'] = df['smoke'] + df['alco'] + (df['cholesterol'] > 1).astype(int) + (df['gluc'] > 1).astype(int)
df['AG'] = df['age'] * df['gluc']
df['CBMI'] = df['cholesterol'] * df['BMI']
df['PPA'] = df['PP'] * df['age']


df = df[[c for c in df.columns if c != 'cardio'] + ['cardio']]
df.to_csv(file, index=False)


# BMI	`weight / (height/100)**2`	体型-代谢风险单指标
# PP (PulsePressure)	`ap_hi - ap_lo`	动脉硬化指标，≥60 高风险
# MAR (MeanArterialPressure)  `(ap_hi + 2*ap_lo)/3`	平均灌注压，比单收/舒更稳
# WPC (WeightPerCm)	`weight / height`	单位身高负载，矮胖者风险
# GPB (GlucPerBMI)	`gluc * BMI`	肥胖+高糖交互
# ABP(AgeBPScore)	`age * (ap_hi/100)`    年龄与收缩压协同，老年高压惩罚       
# RISK(RiskSum)	`smoke + alco + (cholesterol>1) + (gluc>1)`	可改不良生活计数，0-4 量化行为风险
# AG (AgeGluc)	`age * gluc`	年龄×血糖交互，老年糖耐量恶化指标
# CBMI(CholBMI)	`cholesterol * BMI`	高胆固醇+肥胖 → 动脉硬化加速
# PPA (PulsePressureAge) `PP * age`   脉压与年龄交互，老年动脉硬化信号
