# -*- coding: utf-8 -*-
import sys
import os.path
from preprocessing.project_analysis import ProjectAnalysis
import pandas as pd

sys.path.append(os.path.join(os.path.dirname(__file__), '..'))

"""SPLTrac: SPL Traceability Experimental Suite

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""

# START READING THE PROJECTS METADATA
with open('../projects/training_set.dat', 'r') as projects_input_file:

    projects_base_path = projects_input_file.readline().strip('\n')

    data = pd.DataFrame()
    file_index = 1
    for line in projects_input_file:
        (project, language, variability_impl_technology, loc) = line.split()
        path = projects_base_path.replace('\n', '')  # it removes the newline character ('\n') from the path
        project = path + project

        project_analysis = ProjectAnalysis(project, language, variability_impl_technology, loc, data)
        data_frame = project_analysis.run()

        print('\nStep 4: Exporting data to the CSV file...')
        data_frame.to_csv('../projects/training/training_set' + str(file_index) + '.csv')
        data = data.append(data_frame)

        file_index += 1

    data.to_csv('../projects/training/training_set.csv')

    print('DONE\n\n')
