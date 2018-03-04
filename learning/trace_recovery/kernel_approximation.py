from sklearn.kernel_approximation import RBFSampler
from sklearn.linear_model import SGDClassifier
from preprocessing.merge_features_data import get_features_data_frame
from sklearn.externals import joblib

# Choosing the right estimator - http://scikit-learn.org/stable/tutorial/machine_learning_map/index.html
# SGD with kernel approximation - http://scikit-learn.org/stable/modules/kernel_approximation.html


def run_kernel_approximation(config_file):

    print("\n\n- METHOD: Kernel Approximation")
    print("1/4 - Reading training data")
    training_data_frame = get_features_data_frame(config_file)

    print("2/4 - Building training set")
    features_data_frame = training_data_frame.drop(['Feature', 'Document', 'Result'], 1)

    X = features_data_frame.as_matrix()
    y = training_data_frame['Result'].values

    # from sklearn.model_selection import train_test_split
    # X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.4, random_state=0)

    print("3/4 - Fitting the kernel approximation estimator")
    rbf_feature = RBFSampler(gamma=1, random_state=1)
    X_features = rbf_feature.fit_transform(X)
    estimator = SGDClassifier(max_iter=1000)
    estimator.fit(X_features, y)

    # print("4/5 - Calculating the estimator accuracy")
    # X_test_features = rbf_feature.fit_transform(X_test)
    # accuracy = estimator.score(X_test_features, y_test)
    # print("Test set accuracy score: " + str(accuracy))

    print("4/4 - Dumping the kernel approximation estimator")
    joblib.dump(estimator, 'kernel_approximation.pkl')

    # from sklearn import metrics
    # from sklearn.model_selection import ShuffleSplit
    # from learning.plot_learning_curve import plot_learning_curve
    # from sklearn.model_selection cross_val_predict

    # print("\n=== Prediction test ===")
    # result = estimator.predict(X_test)
    # print("Actual: " + str(result))

    # print("\n=== Cross validation results ===")
    # predicted = cross_val_predict(estimator, X, y, cv=5)
    # accuracy_score = metrics.accuracy_score(y, predicted)
    # print("Accuracy score: " + str(accuracy_score))

    # print("\n=== Learning curve ===")
    # Cross validation with 10 iterations to get smoother mean test and train
    # score curves, each time with 20% data randomly selected as a validation set.
    # cv = ShuffleSplit(n_splits=10, test_size=0.2, random_state=0)
    # plot_learning_curve(estimator, X, y, cv)
