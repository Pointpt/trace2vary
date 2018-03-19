from preprocessing.analyzer import perform_projects_pre_processing
from trace_recovery.tracer import fit_machine_learning_models, recover_traces
import config
import sys
import os.path


def print_error_message():
    print('ERROR: you must comply with the following command syntax...')


# MAIN PROGRAM
sys.path.append(os.path.join(os.path.dirname(__file__), '..'))
print('\ntrace2vary: An Algorithm to Recover Feature-Code Traceability and Variability\n')
if len(sys.argv) > 1:
    if len(sys.argv) == 2 and sys.argv[1] == config.pre_process_projects:
        perform_projects_pre_processing()
    elif len(sys.argv) == 3:
        if (sys.argv[1] == config.trace_recovery or sys.argv[1] == config.fit_machine_learning_model)\
                and (sys.argv[2] == config.sgd or sys.argv[2] == config.svm):
            if sys.argv[1] == config.trace_recovery:
                recover_traces(sys.argv[2])
            else:
                fit_machine_learning_models(sys.argv[2])
        else:
            print_error_message()
    else:
        print_error_message()
else:
    print_error_message()
