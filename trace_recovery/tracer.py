from trace_recovery.evaluation.trace_results_evaluator import EvaluationResults
from trace_recovery.evaluation.oracle import TraceabilityOracle
from trace_recovery.svm import svm_fit, svm_load, svm_predict
from trace_recovery.sgd import sgd_fit, sgd_load, sgd_predict
from preprocessing.merge_features_data import get_features_data_frame_per_project
# from learning.trace_recovery.auto_learning import auto_learning_fit, auto_learning_load, auto_learning_predict
import time
import config
import json


def fit_machine_learning_models(only_sgd):

    print("===== METHODS FITTING PROCESS =====\n")

    # Stochastic Gradient Descent method
    sgd_fit(config.training_set_file)

    if not only_sgd:
        print("\n")
        svm_fit(config.training_set_file)  # Support Vector Machine method
        # auto_learning_fit()  # Auto Learning method


def recover_traces(only_sgd):

    print("===== TRACE RECOVERY PROCESS =====")

    with open(config.test_set_file, 'r') as projects_input_file:

        evaluation_results = EvaluationResults()

        try:

            print("1/3 - Loading machine learning models")
            projects_base_path = projects_input_file.readline().strip('\n')

            sgd = sgd_load()

            if not only_sgd:
                svm = svm_load()
                # estimator = auto_learning_load()

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
                    loc,
                    true_traces
                )

                project_data_frame = get_features_data_frame_per_project(projects_base_path, project)

                apply_machine_learning_method(
                    sgd, project_data_frame, project, projects_base_path, config.sgd, evaluation_results
                )

                if not only_sgd:
                    apply_machine_learning_method(
                        svm, project_data_frame, project, projects_base_path, config.svm, evaluation_results
                    )

            print("\n3/3 - Consolidating project results")
            evaluation_results.export_results()

            print('DONE')

        except FileNotFoundError:
            print("ERROR: machine learning models are not available. Aborting trace recovery...")


def apply_machine_learning_method(
        method, project_data_frame, project, projects_base_path, method_name, evaluation_results
):
    performance = time.time()
    result = None
    if method_name == config.sgd:
        result = sgd_predict(method, project_data_frame)
    elif method_name == config.svm:
        result = svm_predict(method, project_data_frame)
    performance = time.time() - performance
    traces = extract_method_traces(project, project_data_frame, result)
    with open(projects_base_path + project + '/' + method_name + '_traces.json', 'w') as result_file:
        result_file.write(json.dumps(traces))
    evaluation_results.add_method_results(project, method_name.upper(), traces, performance)


def extract_method_traces(project, project_data_frame, result):
    traces = {}
    for index, row in project_data_frame.iterrows():
        if result[index] == 1:
            feature_name = row['Feature']
            document = row['Document'].split(project + '/')[-1]
            if feature_name in traces:
                traces[feature_name] += (document,)
            else:
                traces[feature_name] = (document,)
    return traces
