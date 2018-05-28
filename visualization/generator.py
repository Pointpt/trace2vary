import glob
import os.path
import json
from visualization.features_view import create_burtin_chart
from visualization.traced_files_view import create_general_data_view


def build_views():
    print('\n===== COMMONALITY AND VARIABILITY ANALYSIS =====')

    candidate_output_files_list = glob.glob("output/*.t2v")
    print('\nAvailable output files:')
    for index, value in enumerate(candidate_output_files_list):
        print('(' + str(index + 1) + ') - ' + value)

    file_number = 0
    try:
        file_number = int(
            input('\nChoose the file to read by its number (or provide a file path manually): ')
        )
        selected_file = candidate_output_files_list[file_number - 1]
    except ValueError:
        selected_file = file_number
        if not os.path.isfile(selected_file):
            print('ERROR: file name does not exist. Aborting visualization.\n')
            exit(0)
    except IndexError:
        print('ERROR: file number does not exist. Aborting visualization.\n')
        exit(0)

    with open(selected_file, 'r') as trace2vary_output_file:
        trace2vary_output = json.load(trace2vary_output_file)
        print('1/2 - Creating general data visualization')
        # create_general_data_view(trace2vary_output)
        print('2/2 - Creating consolidated features visualization')
        create_burtin_chart(trace2vary_output)
