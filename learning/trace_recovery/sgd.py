import numpy as np
from sklearn.linear_model import SGDClassifier
from sklearn.model_selection import GridSearchCV
from sklearn.preprocessing import StandardScaler
from preprocessing.merge_features_data import get_features_data_frame
from sklearn.externals import joblib

# Choosing the right estimator - http://scikit-learn.org/stable/tutorial/machine_learning_map/index.html
# SGD - http://scikit-learn.org/stable/modules/sgd.html


def run_sgd(config_file):

    print("\n\n- METHOD: Stochastic Gradient Descent")
    print("1/6 - Reading training data")
    training_data_frame = get_features_data_frame(config_file)

    print("2/6 - Building training set")
    features_data_frame = training_data_frame.drop(['Feature', 'Document', 'Result'], 1)

    X = features_data_frame.as_matrix()
    y = training_data_frame['Result'].values

    # from sklearn.model_selection import train_test_split
    # X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.4, random_state=0)

    print("3/6 - Applying feature scaling")
    # Stochastic Gradient Descent is sensitive to feature scaling, so it is highly recommended to scale your data.
    # For example, scale each attribute on the input vector X to [0,1] or [-1,+1],
    # or standardize it to have mean 0 and variance 1.
    # Note that the same scaling must be applied to the test vector to obtain meaningful results.
    scaler = StandardScaler()
    scaler.fit(X)
    X = scaler.transform(X)
    # X_test = scaler.transform(X_test)

    print("4/6 - Finding the alpha regularization term")
    # Finding a reasonable regularization term \alpha is best done using GridSearchCV,
    # usually in the range 10.0**-np.arange(1,7).
    alphas = 10.0**-np.arange(1, 7)
    grid = GridSearchCV(estimator=SGDClassifier(max_iter=1000), param_grid=dict(alpha=alphas))
    grid.fit(X, y)

    print("5/6 - Fitting the SGD estimator")
    # Empirically, we found that SGD converges after observing approx. 10^6 training samples.
    # Thus, a reasonable first guess for the number of iterations is n_iter = np.ceil(10**6 / n),
    # where n is the size of the training set.
    max = np.ceil(10**6 / len(X))

    estimator = SGDClassifier(loss='hinge', penalty='l2', alpha=grid.best_estimator_.alpha, max_iter=max)
    estimator.fit(X, y)

    # print("6/7 - Calculating the estimator accuracy")
    # accuracy = estimator.score(X_test, y_test)
    # print("Test set accuracy score: " + str(accuracy))

    print("6/6 - Dumping the SGD estimator")
    joblib.dump(estimator, 'sgd.pkl')

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
