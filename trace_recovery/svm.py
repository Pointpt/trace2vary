from sklearn import svm
from sklearn.preprocessing import StandardScaler
from preprocessing.merge_features_data import get_features_data_frame
from sklearn.externals import joblib
import config

# Choosing the right estimator - http://scikit-learn.org/stable/tutorial/machine_learning_map/index.html
# SVM - http://scikit-learn.org/stable/modules/svm.html

ESTIMATOR_FILE_NAME = config.svm_file
scaler = StandardScaler()


def svm_fit(config_file):

    print("- METHOD: Support Vector Machine")
    print("1/5 - Reading training data")
    training_data_frame = get_features_data_frame(config_file)

    print("2/5 - Building training set")
    features_data_frame = training_data_frame.drop(['Feature', 'Document', 'Result'], 1)

    X = features_data_frame.as_matrix()
    y = training_data_frame['Result'].values

    print("3/5 - Applying feature scaling")
    # Support Vector Machine algorithms are not scale invariant, so it is highly recommended to scale your data.
    # For example, scale each attribute on the input vector X to [0,1] or [-1,+1],
    # or standardize it to have mean 0 and variance 1.
    # Note that the same scaling must be applied to the test vector to obtain meaningful results.
    scaler.fit(X)
    X = scaler.transform(X)

    print("4/5 - Fitting the SVC estimator")
    # 1) C is 1 by default and it’s a reasonable default choice.
    # If you have a lot of noisy observations you should decrease it.
    # It corresponds to regularize more the estimation.
    #
    # 2) Kernel cache size: For SVC, SVR, nuSVC and NuSVR,
    # the size of the kernel cache has a strong impact on run times for larger problems.
    # If you have enough RAM available, it is recommended to set cache_size
    # to a higher value than the default of 200(MB), such as 500(MB) or 1000(MB).
    #
    # 3) In SVC, if data for classification are unbalanced (e.g. many positive and few negative),
    # set class_weight='balanced' and/or try different penalty parameters C.
    estimator = svm.SVC(gamma='auto', C=1.0, kernel='rbf', cache_size=1000, class_weight='balanced')
    estimator.fit(X, y)

    print("5/5 - Dumping the SVC estimator")
    joblib.dump(estimator, ESTIMATOR_FILE_NAME)


def svm_load():
    estimator = joblib.load(ESTIMATOR_FILE_NAME)
    return estimator


def svm_predict(estimator, data_frame):
    features_data_frame = data_frame.drop(['Feature', 'Document', 'Result'], 1)
    X = features_data_frame.as_matrix()
    scaler.fit(X)
    X = scaler.transform(X)
    result = estimator.predict(X)
    return result
