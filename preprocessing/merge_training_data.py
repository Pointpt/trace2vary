import glob
import os
import pandas as pd

os.chdir("../projects/training")

data = pd.DataFrame()

for file in glob.glob("*.csv"):
    data_frame = pd.read_csv(file, index_col=0)
    data = data.append(data_frame)

data.to_csv('full_training_set.csv')
