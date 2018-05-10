from preprocessing.analyzer import perform_projects_pre_processing
from trace_recovery.tracer import fit_machine_learning_models, recover_traces
import config
import sys
import os.path


def print_error_message():
    print(
        '[ERROR] You must comply with the following command syntax:\n\n'
        '\tpython3 trace2vary.py <options> [method]\n\n'
        '<options>\n'
        '\t-p    \tApply pre-processing for the project to be analyzed.\n'
        '\t-fit  \tFit the machine learning model considering the training set. It requires the [method] argument.\n'
        '\t-tr   \tRecovery traces for the analyzed project.\n'
        '\t-cv   \tPerforms the commonality and variability (C & V) analysis for the stated products\'projects.\n\n'
        '[-only-sgd]\n'
        '\tIt runs only the Stochastic Gradient Descent method for the requested task.\n'
        '\tThis is not applied to the -p and -cv options, since they do not use '
        'a machine learning algorithm to accomplish the task.\n\n'
        'Examples:\n'
        '\tpython3 trace2vary.py -p\n'
        '\tpython3 trace2vary.py -p\n'
        '\tpython3 trace2vary.py -fit\n'
        '\tpython3 trace2vary.py -fit -only-sgd\n'
        '\tpython3 trace2vary.py -tr\n'
        '\tpython3 trace2vary.py -tr -only-sgd\n'
        '\tpython3 trace2vary.py -cv\n'
    )


def check_only_sgd_argument(arguments_list):
    sgd = False
    if len(arguments_list) == 3:
        if arguments_list[2] == config.arg_only_sgd:
            sgd = True
        else:
            print_error_message()
            exit(0)
    return sgd


# MAIN PROGRAM
sys.path.append(os.path.join(os.path.dirname(__file__), '..'))
print('\ntrace2vary: An Algorithm to Recover Feature-Code Traceability and Variability\n')

if 1 <= len(sys.argv) <= 3:
    if sys.argv[1] == config.arg_pre_process_projects and len(sys.argv) < 3:
        perform_projects_pre_processing()
    elif sys.argv[1] == config.arg_fit_machine_learning_model:
        only_sgd = check_only_sgd_argument(sys.argv)
        fit_machine_learning_models(only_sgd)
    elif sys.argv[1] == config.arg_trace_recovery:
        only_sgd = check_only_sgd_argument(sys.argv)
        recover_traces(only_sgd)
    elif sys.argv[1] == config.arg_cv_analysis and len(sys.argv) < 3:
        print('C&V analysis...')
    else:
        print_error_message()
else:
    print_error_message()
