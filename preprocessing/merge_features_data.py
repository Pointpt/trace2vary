import pandas as pd


def get_features_data_frame(config_file):

    data = pd.DataFrame()

    with open(config_file, 'r') as projects_input_file:
        projects_base_path = projects_input_file.readline().strip('\n')
        for line in projects_input_file:
            (project, language, variability_impl_technology, loc) = line.split()
            data_frame = pd.read_csv(projects_base_path + project + '/data.csv', index_col=0)
            data = data.append(data_frame)

    return data

