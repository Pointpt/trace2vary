import pandas as pd

"""trace2vary: An Algorithm to Recover Feature-Code Traceability and Variability

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""


def get_features_data_frame(config_file):
    """
    It reads the CSV features' results file and transforms the data into a Pandas DataFrame
    :param config_file: file containing projects metadata to be analyzed
    :return: resulting data frame
    """

    data = pd.DataFrame()

    with open(config_file, 'r') as projects_input_file:
        projects_base_path = projects_input_file.readline().strip('\n')
        for line in projects_input_file:
            project = line.split()[0]
            data_frame = pd.read_csv(projects_base_path + project + '/data.csv', index_col=0)
            data = data.append(data_frame)

    return data


def get_features_data_frame_per_project(base_path, project):
    """
    It reads the CSV features' results file per project and transforms the data into a Pandas DataFrame
    :param base_path: project location
    :param project: project name
    :return: resulting data frame
    """

    data_frame = pd.read_csv(base_path + project + '/data.csv', index_col=0)

    return data_frame
