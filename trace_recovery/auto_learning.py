from auto_ml import Predictor
from auto_ml.utils_models import load_ml_model
from preprocessing.merge_features_data import get_features_data_frame
import config


# https://automl.github.io/auto-sklearn/stable/#example

ESTIMATOR_FILE_NAME = config.auto_learning_file

column_descriptions = {
    'Result': 'output'
}


def auto_learning_fit(config_file):

    print("\n\n- METHOD: Auto Leaning")
    print("1/4 - Reading training data")
    training_data_frame = get_features_data_frame(config_file)

    print("2/4 - Building training set")
    features_data_frame = training_data_frame.drop(['Feature', 'Document'], 1)
    training_data_frame.columns = training_data_frame.columns.values

    print("3/4 - Finding the best estimator")
    estimator = Predictor(type_of_estimator='classifier', column_descriptions=column_descriptions)

    estimator.train(features_data_frame)

    print("4/4 - Dumping the SGD estimator")
    estimator.save(ESTIMATOR_FILE_NAME)


def auto_learning_load():
    estimator = load_ml_model(ESTIMATOR_FILE_NAME)
    return estimator


def auto_learning_predict(estimator, data_frame_row):
    features_data_frame = data_frame_row.drop(['Feature', 'Document', 'Result'], 1)
    features_data_frame.columns = features_data_frame.columns.values
    result = estimator.predict(features_data_frame)
    return result

