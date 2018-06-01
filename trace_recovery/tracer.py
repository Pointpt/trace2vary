from trace_recovery.evaluation.trace_results_evaluator import EvaluationResults
from trace_recovery.evaluation.oracle import TraceabilityOracle
from trace_recovery.sgd import sgd_fit, sgd_load, sgd_predict
from preprocessing.merge_features_data import get_features_data_frame_per_project
from trace_recovery.auto_learning import auto_learning_fit, auto_learning_load, auto_learning_predict
import time
import config
import json

"""trace2vary: An Algorithm to Recover Feature-Code Traceability and Variability

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""


def fit_machine_learning_models(only_default_method):
    """
    It calls the functions related to the machine learning models required by the user's command.
    :param only_default_method: boolean value indicating if only the SGD model will be used
    """

    print("\n===== METHODS FITTING PROCESS =====\n")

    # Stochastic Gradient Descent method
    sgd_fit(config.training_set_file)

    if not only_default_method:
        print("\n")
        auto_learning_fit(config.training_set_file)  # Auto Learning method


def recover_traces(only_default_method):
    """
    It performs the trace recovery for all projects in the configuration file.
    :param only_default_method: boolean value indicating if only the SGD model will be used
    """

    print("\n===== TRACE RECOVERY PROCESS =====")

    with open(config.test_set_file, 'r') as projects_input_file:
        evaluation_results = EvaluationResults()
        try:
            print("1/3 - Loading machine learning models")
            projects_base_path = projects_input_file.readline().strip('\n')

            sgd = sgd_load()
            if not only_default_method:
                auto_learning = auto_learning_load()

            print("2/3 - Predicting traces for projects\n")
            for line in projects_input_file:
                (project, language, variability_impl_technology, files, loc, features) = line.split()
                print("Project: " + project)

                project_oracle = TraceabilityOracle(projects_base_path, project)
                true_traces = project_oracle.extract_true_traces()

                evaluation_results.add_project_input_data(
                    project,
                    variability_impl_technology,
                    language,
                    files,
                    loc,
                    true_traces
                )

                project_data_frame = get_features_data_frame_per_project(projects_base_path, project)

                apply_machine_learning_method(
                    sgd, project_data_frame, project,
                    projects_base_path, config.sgd, evaluation_results
                )

                if not only_default_method:
                    apply_machine_learning_method(
                        auto_learning, project_data_frame, project,
                        projects_base_path, config.auto_learning, evaluation_results
                    )
            print("\n3/3 - Consolidating project results")
            evaluation_results.export_results()

        except FileNotFoundError as f:
            print('ERROR: machine learning models are not available. Aborting trace recovery...')
            print('Message: ' + str(f))


def apply_machine_learning_method(
        method, project_data_frame, project, projects_base_path, method_name, evaluation_results
):
    """
    It executes a given machine learning method a saves its results.
    :param method: machine learning model to be executed
    :param project_data_frame: input data for analysis
    :param project: project name
    :param projects_base_path: project location
    :param method_name: machine learning model name
    :param evaluation_results: evaluation results object to be updated
    """
    performance = time.time()

    result = None
    if method_name == config.sgd:
        result = sgd_predict(method, project_data_frame)
    elif method_name == config.auto_learning:
        result = auto_learning_predict(method, project_data_frame)

    performance = time.time() - performance
    traces = extract_method_traces(project, project_data_frame, result)
    with open(projects_base_path + project + '/' + method_name + '_traces.json', 'w') as result_file:
        result_file.write(json.dumps(traces))
    evaluation_results.add_method_results(project, method_name.upper(), traces, performance)


def extract_method_traces(project, project_data_frame, result):
    """
    It gets the data frame result and creates the traces dictionary result data structure.
    :param project: project name
    :param project_data_frame: data frame object
    :param result: traces dictionary
    """
    traces = {}
    for index, row in project_data_frame.iterrows():
        if result[index] == 1:
            feature_name = row['Feature']
            document = row['Document'].split(project + '/')[-1]
            if len(feature_name) > 1:
                if feature_name in traces:
                    traces[feature_name] += (document,)
                else:
                    traces[feature_name] = (document,)
    return traces
