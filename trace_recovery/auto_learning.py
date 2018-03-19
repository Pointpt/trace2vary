from sklearn.model_selection import train_test_split
from sklearn import preprocessing
import autosklearn.classification
from preprocessing.merge_features_data import get_features_data_frame
from sklearn.externals import joblib

# https://automl.github.io/auto-sklearn/stable/#example

ESTIMATOR_FILE_NAME = 'auto_learning.pkl'


def auto_learning_fit(config_file):

    print("\n\n- METHOD: Auto Leaning")
    print("1/4 - Reading training data")
    training_data_frame = get_features_data_frame(config_file)

    print("2/4 - Building training set")
    features_data_frame = training_data_frame.drop(['Feature', 'Document', 'Result'], 1)
    features_matrix = features_data_frame.as_matrix()
    X = preprocessing.normalize(features_matrix)  # normalizing features' values
    y = training_data_frame['Result'].values

    # X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.4, random_state=0)

    print("3/4 - Finding the best estimator")
    estimator = autosklearn.classification.AutoSklearnClassifier()
    estimator.fit(X, y)

    # print("4/5 - Calculating the estimator accuracy")
    # accuracy = estimator.score(X_test, y_test)
    # print("Test set accuracy score: " + str(accuracy))

    print("4/4 - Dumping the SGD estimator")
    joblib.dump(estimator, ESTIMATOR_FILE_NAME)


def auto_learning_load():
    estimator = joblib.load(ESTIMATOR_FILE_NAME)
    return estimator


def auto_learning_predict(estimator, data_frame_row):
    features_data_frame = data_frame_row.drop(['Feature', 'Document', 'Result'], 1)
    X = features_data_frame.as_matrix()
    result = estimator.predict(X)
    return result

