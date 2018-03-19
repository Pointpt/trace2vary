from trace_recovery.evaluation.trace_results_evaluator import EvaluationResults
from trace_recovery.evaluation.oracle import TraceabilityOracle
from trace_recovery.svm import svm_fit, svm_load, svm_predict
from trace_recovery.sgd import sgd_fit, sgd_load, sgd_predict
from preprocessing.merge_features_data import get_features_data_frame_per_project
# from learning.trace_recovery.auto_learning import auto_learning_fit, auto_learning_load, auto_learning_predict
import time
import config


def fit_machine_learning_models(method):

    print("===== METHODS FITTING PROCESS =====")

    if method == config.svm:
        # Support Vector Machine method
        svm_fit(config.training_set_file)
    elif method == config.sgd:
        # Stochastic Gradient Descent method
        sgd_fit(config.training_set_file)
    # else:
        # Auto Learning method
        # auto_learning_fit()


def recover_traces(method):

    print("===== TRACE RECOVERY PROCESS =====")

    with open(config.test_set_file, 'r') as projects_input_file:

        evaluation_results = EvaluationResults()

        try:

            print("1/3 - Loading machine learning models")
            projects_base_path = projects_input_file.readline().strip('\n')

            svm = svm_load()
            sgd = sgd_load()

            # if method == config.svm:
                # estimator = svm_load()
            # elif method == config.sgd:
                # estimator = sgd_load()
            # else:
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

                performance = time.time()
                svm_result = svm_predict(svm, project_data_frame)
                performance = time.time() - performance
                svm_traces = extract_method_traces(project, project_data_frame, svm_result)
                evaluation_results.add_method_results(project, 'SVM', svm_traces, performance)

                performance = time.time()
                sgd_result = sgd_predict(sgd, project_data_frame)
                performance = time.time() - performance
                sgd_traces = extract_method_traces(project, project_data_frame, sgd_result)
                evaluation_results.add_method_results(project, 'SGD', sgd_traces, performance)

            print("\n3/3 - Consolidating project results")
            evaluation_results.export_results()

            print('DONE')

        except FileNotFoundError:
            print("ERROR: machine learning models are not available. Aborting trace recovery...")


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
