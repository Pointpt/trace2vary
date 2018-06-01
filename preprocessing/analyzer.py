from preprocessing.project_analysis import ProjectAnalysis
import pandas as pd

"""trace2vary: An Algorithm to Recover Feature-Code Traceability and Variability

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""


def perform_projects_pre_processing(config_file):
    """
    It starts the preprocessing trace2vary step.
    :param config_file: file containing projects metadata to be analyzed
    """

    print("\n===== PROJECTS PRE-PROCESSING =====")

    # START READING THE PROJECTS METADATA
    with open(config_file, 'r') as projects_input_file:

        projects_base_path = projects_input_file.readline().strip('\n')

        data = pd.DataFrame()
        file_index = 1
        for line in projects_input_file:
            (project, language, variability_impl_technology, files, loc, features) = line.split()
            path = projects_base_path.replace('\n', '')  # it removes the newline character ('\n') from the path
            project = path + project

            project_analysis = ProjectAnalysis(project, language, variability_impl_technology, files, loc, features, data)
            data_frame = project_analysis.run()

            print('\n4/4 - Exporting data to the CSV file...')
            data_frame.to_csv(project + '/data.csv')
            data = data.append(data_frame)

            file_index += 1
