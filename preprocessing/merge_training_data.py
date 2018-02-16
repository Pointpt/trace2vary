import glob
import os
import pandas as pd


def get_training_data_frame():

    data = pd.DataFrame()

    for file in glob.glob("../../projects/training/**/*training_set.csv", recursive=True):
        # print('Reading ' + file)
        data_frame = pd.read_csv(file, index_col=0)
        data = data.append(data_frame)

    return data

