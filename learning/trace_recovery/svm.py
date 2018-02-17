from sklearn import svm
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from preprocessing.merge_training_data import get_training_data_frame
from sklearn.externals import joblib

# Choosing the right estimator - http://scikit-learn.org/stable/tutorial/machine_learning_map/index.html
# SVM - http://scikit-learn.org/stable/modules/svm.html


def run_svm():

    print("\n\n- METHOD: Support Vector Machine")
    print("1/6 - Reading training data")
    training_data_frame = get_training_data_frame()

    print("2/6 - Building training and test sets")
    features_data_frame = training_data_frame.drop(['Feature', 'Document', 'Result'], 1)

    X = features_data_frame.as_matrix()
    y = training_data_frame['Result'].values

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.4, random_state=0)

    print("3/6 - Applying feature scaling")
    # Support Vector Machine algorithms are not scale invariant, so it is highly recommended to scale your data.
    # For example, scale each attribute on the input vector X to [0,1] or [-1,+1],
    # or standardize it to have mean 0 and variance 1.
    # Note that the same scaling must be applied to the test vector to obtain meaningful results.
    scaler = StandardScaler()
    scaler.fit(X_train)
    X_train = scaler.transform(X_train)
    X_test = scaler.transform(X_test)

    print("4/6 - Fitting the SVC estimator")
    # 1) C is 1 by default and it’s a reasonable default choice.
    # If you have a lot of noisy observations you should decrease it.
    # It corresponds to regularize more the estimation.
    #
    # 2) Kernel cache size: For SVC, SVR, nuSVC and NuSVR,
    # the size of the kernel cache has a strong impact on run times for larger problems.
    # If you have enough RAM available, it is recommended to set cache_size to a higher value than the default of 200(MB),
    # such as 500(MB) or 1000(MB).
    #
    # 3) In SVC, if data for classification are unbalanced (e.g. many positive and few negative),
    # set class_weight='balanced' and/or try different penalty parameters C.
    estimator = svm.SVC(gamma='auto', C=1.0, kernel='rbf', cache_size=1000, class_weight='balanced')
    estimator.fit(X_train, y_train)

    print("5/6 - Calculating the estimator accuracy")
    accuracy = estimator.score(X_test, y_test)
    print("Test set accuracy score: " + str(accuracy))

    print("6/6 - Dumping the SVC estimator")
    joblib.dump(estimator, 'svm.pkl')

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
