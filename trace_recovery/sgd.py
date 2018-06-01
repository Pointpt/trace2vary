import numpy as np
from sklearn.linear_model import SGDClassifier
from sklearn.preprocessing import StandardScaler
from preprocessing.merge_features_data import get_features_data_frame
from sklearn.externals import joblib
import config

"""trace2vary: An Algorithm to Recover Feature-Code Traceability and Variability

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br

References:
Choosing the right estimator - http://scikit-learn.org/stable/tutorial/machine_learning_map/index.html
SGD - http://scikit-learn.org/stable/modules/sgd.html
"""

ESTIMATOR_FILE_NAME = config.sgd_file
scaler = StandardScaler()


def sgd_fit(config_file):
    """
    It performs the machine learning method fitting for the SGD algorithm
    :param config_file: file containing the projects metadata
    """

    print('- METHOD: Stochastic Gradient Descent')
    print('1/5 - Reading training data')
    training_data_frame = get_features_data_frame(config_file)

    print('2/5 - Building training set')
    features_data_frame = training_data_frame.drop(['Feature', 'Document', 'Result'], 1)

    X = features_data_frame.as_matrix()
    y = training_data_frame['Result'].values

    print('3/5 - Applying feature scaling')
    # Stochastic Gradient Descent is sensitive to feature scaling, so it is highly recommended to scale your data.
    # For example, scale each attribute on the input vector X to [0,1] or [-1,+1],
    # or standardize it to have mean 0 and variance 1.
    # Note that the same scaling must be applied to the test vector to obtain meaningful results.
    scaler.fit(X)
    X = scaler.transform(X)

    print('4/5 - Fitting the SGD estimator')
    # Empirically, we found that SGD converges after observing approx. 10^6 training samples.
    # Thus, a reasonable first guess for the number of iterations is n_iter = np.ceil(10**6 / n),
    # where n is the size of the training set.
    max = np.ceil(10**6 / len(X))

    estimator = SGDClassifier(loss='hinge', penalty='l2', max_iter=max, shuffle=True)
    estimator.fit(X, y)

    print('5/5 - Dumping the SGD estimator')
    joblib.dump(estimator, ESTIMATOR_FILE_NAME)


def sgd_load():
    """
    It loads the machine learning model used during the analysis
    :return: SGD model object
    """
    estimator = joblib.load(ESTIMATOR_FILE_NAME)
    return estimator


def sgd_predict(estimator, data_frame):
    """
    It predicts the traceability result for a given feature-document pair
    :param estimator: SGD model object
    :param data_frame_row: input data for the machine learning method
    :return: resulting value (relevant - 1 or non-relevant - 0)
    """
    features_data_frame = data_frame.drop(['Feature', 'Document', 'Result'], 1)
    X = features_data_frame.as_matrix()
    scaler.fit(X)
    X = scaler.transform(X)
    result = estimator.predict(X)
    return result
