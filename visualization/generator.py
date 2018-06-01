import glob
import os.path
import json
from bokeh.models.widgets import Panel, Tabs
from bokeh.io import output_file, show
from visualization.traced_files_view import create_general_data_view
from visualization.table_view import create_table

"""trace2vary: An Algorithm to Recover Feature-Code Traceability and Variability

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""


def build_views():
    """
    It calls the plot creators and exports the results to an HTML file.
    """
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
        general_plot = create_general_data_view(trace2vary_output)
        general_tab = Panel(child=general_plot, title='General')

        # print('2/3 - Creating consolidated features visualization')
        # features_plot = create_burtin_chart(trace2vary_output)
        # features_tab = Panel(child=features_plot, title='Features')

        print('2/2 - Creating table with raw data')
        table_plot = create_table(trace2vary_output)
        table_tab = Panel(child=table_plot, title='Raw data')

        tabs = Tabs(tabs=[general_tab, table_tab])

        output_file('output/trace2vary_result.html', title='trace2vary - Results')
        show(tabs)
