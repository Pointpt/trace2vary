from preprocessing.analyzer import perform_projects_pre_processing
from trace_recovery.tracer import fit_machine_learning_models, recover_traces
from commonality_and_variability.cv_analyzer import compare_products
from visualization.generator import build_views
import config
import sys
import os.path


def print_error_message():
    print(
        '[ERROR] You must comply with the following command syntax:\n\n'
        '\tpython3 trace2vary.py <options> [-default]\n\n'
        '<options>\n'
        '\t-p    \tApply pre-processing for the project to be analyzed.\n'
        '\t-fit  \tFit the machine learning model considering the training set. It requires the [method] argument.\n'
        '\t-tr   \tRecovery traces for the analyzed project.\n'
        '\t-cv     Performs the commonality and variability (C & V) analysis for the stated products\' projects.\n'
        '\t-vis    Starts the visualization client for the trace2vary output file.\n'
        '\t-core   Runs the -p, -tr (with the default method), -cv and -vis tasks in a sequential way.\n'
        '\t-pre    Prepares trace2vary for the core tasks, by running the -p and -fit tasks with the default method.\n\n'
        '[-default]\n'
        '\tIt runs only the default method, Stochastic Gradient Descent, for the requested task.\n'
        'This is not applied to the -p, -cv, and -vis options,\n'
        'since they do not use a machine learning algorithm to accomplish the task.\n\n'
        'Examples:\n'
        '\tpython3 trace2vary.py -core\n'
        '\tpython3 trace2vary.py -pre\n'
        '\tpython3 trace2vary.py -p\n'
        '\tpython3 trace2vary.py -fit\n'
        '\tpython3 trace2vary.py -fit -default\n'
        '\tpython3 trace2vary.py -tr\n'
        '\tpython3 trace2vary.py -tr -default\n'
        '\tpython3 trace2vary.py -cv\n'
        '\tpython3 trace2vary.py -vis\n'
    )


def check_only_default_method_argument(arguments_list):
    default_method = False
    if len(arguments_list) == 3:
        if arguments_list[2] == config.arg_only_default_method:
            default_method = True
        else:
            print_error_message()
            exit(0)
    return default_method


# MAIN PROGRAM
sys.path.append(os.path.join(os.path.dirname(__file__), '..'))
print('\ntrace2vary: An Algorithm to Recover Feature-Code Traceability and Variability\n')

if 1 <= len(sys.argv) <= 3:
    if sys.argv[1] == config.arg_fit_machine_learning_model:
        only_default_method = check_only_default_method_argument(sys.argv)
        fit_machine_learning_models(only_default_method)
    elif sys.argv[1] == config.arg_trace_recovery:
        only_default_method = check_only_default_method_argument(sys.argv)
        recover_traces(only_default_method)
    elif len(sys.argv) < 3:
        if sys.argv[1] == config.arg_pre_process_projects:
            perform_projects_pre_processing(config.complete_set_file)
        elif sys.argv[1] == config.arg_cv_analysis:
            compare_products()
        elif sys.argv[1] == config.arg_visualization:
            build_views()
        elif sys.argv[1] == config.arg_recovery_preparation:
            perform_projects_pre_processing(config.training_set_file)
            only_default_method = True
            fit_machine_learning_models(only_default_method)
        elif sys.argv[1] == config.arg_core_tasks:
            perform_projects_pre_processing(config.test_set_file)
            only_default_method = True
            recover_traces(only_default_method)
            compare_products()
            build_views()
        else:
            print_error_message()
    else:
        print_error_message()
else:
    print_error_message()

print('DONE\n\n')
