from auto_ml import Predictor
from auto_ml.utils_models import load_ml_model
from preprocessing.merge_features_data import get_features_data_frame
import config

"""trace2vary: An Algorithm to Recover Feature-Code Traceability and Variability

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br

References used in this file:
auto_ml: Automated machine learning for production and analytics
https://github.com/ClimbsRocks/auto_ml
"""

ESTIMATOR_FILE_NAME = config.auto_learning_file

column_descriptions = {
    'Result': 'output'
}


def auto_learning_fit(config_file):
    """
    It performs the machine learning method fitting for the auto learning algorithm
    :param config_file: file containing the projects metadata
    """

    print('- METHOD: Auto Leaning')
    print('1/4 - Reading training data')
    training_data_frame = get_features_data_frame(config_file)

    print('2/4 - Building training set')
    features_data_frame = training_data_frame.drop(['Feature', 'Document'], 1)
    features_data_frame['Result'] = features_data_frame['Result'].astype(int)
    training_data_frame.columns = training_data_frame.columns.values

    print('3/4 - Finding the best estimator')
    estimator = Predictor(type_of_estimator='classifier', column_descriptions=column_descriptions)

    estimator.train(features_data_frame)

    print('4/4 - Dumping the SGD estimator')
    estimator.save(ESTIMATOR_FILE_NAME)


def auto_learning_load():
    """
    It loads the machine learning model used during the analysis
    :return: auto learning model object
    """
    estimator = load_ml_model(ESTIMATOR_FILE_NAME)
    return estimator


def auto_learning_predict(estimator, data_frame_row):
    """
    It predicts the traceability result for a given feature-document pair
    :param estimator: auto learning model object
    :param data_frame_row: input data for the machine learning method
    :return: resulting value (relevant - 1 or non-relevant - 0)
    """
    features_data_frame = data_frame_row.drop(['Feature', 'Document', 'Result'], 1)
    features_data_frame.columns = features_data_frame.columns.values
    result = estimator.predict(features_data_frame)
    return result

