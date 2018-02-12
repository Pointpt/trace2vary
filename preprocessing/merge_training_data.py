import glob
import os
import pandas as pd


def get_training_data_frame():

    os.chdir("../projects/training")

    data = pd.DataFrame()

    for file in glob.glob("*training_set.csv", recursive=True):
        data_frame = pd.read_csv(file, index_col=0)
        data = data.append(data_frame)

    return data

