from sklearn.model_selection import train_test_split
from sklearn import preprocessing
import autosklearn.classification
from preprocessing.merge_training_data import get_training_data_frame
from sklearn.externals import joblib

# https://automl.github.io/auto-sklearn/stable/#example


def run_auto_learning():

    print("\n\n- METHOD: Auto Leaning")
    print("1/5 - Reading training data")
    training_data_frame = get_training_data_frame()

    print("2/5 - Building training and test sets")
    features_data_frame = training_data_frame.drop(['Feature', 'Document', 'Result'], 1)
    features_matrix = features_data_frame.as_matrix()
    X = preprocessing.normalize(features_matrix)  # normalizing features' values
    y = training_data_frame['Result'].values

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.4, random_state=0)

    print("3/5 - Finding the best estimator")
    estimator = autosklearn.classification.AutoSklearnClassifier()
    estimator.fit(X_train, y_train)

    print("4/5 - Calculating the estimator accuracy")
    accuracy = estimator.score(X_test, y_test)
    print("Test set accuracy score: " + str(accuracy))

    print("5/5 - Dumping the SGD estimator")
    joblib.dump(estimator, 'auto_learning.pkl')
