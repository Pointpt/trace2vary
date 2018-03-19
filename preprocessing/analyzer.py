from preprocessing.project_analysis import ProjectAnalysis
import pandas as pd
import config

"""SPLTrac: SPL Traceability Experimental Suite

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""


def perform_projects_pre_processing():

    # START READING THE PROJECTS METADATA
    with open(config.complete_set_file, 'r') as projects_input_file:

        projects_base_path = projects_input_file.readline().strip('\n')

        data = pd.DataFrame()
        file_index = 1
        for line in projects_input_file:
            (project, language, variability_impl_technology, files, loc, features) = line.split()
            path = projects_base_path.replace('\n', '')  # it removes the newline character ('\n') from the path
            project = path + project

            project_analysis = ProjectAnalysis(project, language, variability_impl_technology, files, loc, features, data)
            data_frame = project_analysis.run()

            print('\nStep 4: Exporting data to the CSV file...')
            data_frame.to_csv('../projects/' + project + '/data.csv')
            data = data.append(data_frame)

            file_index += 1

        print('DONE\n\n')
