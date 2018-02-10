import pandas as pd
from sklearn import svm
from sklearn.model_selection import train_test_split, cross_val_predict
from sklearn import metrics, preprocessing
from sklearn.model_selection import ShuffleSplit
from learning.plot_learning_curve import plot_learning_curve

print("Creating estimator...")
training_data_frame = pd.read_csv("../projects/training/full_training_set.csv")

features_data_frame = training_data_frame.drop(['Feature', 'Document', 'Result'], 1)
features_matrix = features_data_frame.as_matrix()
X = preprocessing.normalize(features_matrix)  # normalizing features' values

y = training_data_frame['Result'].values

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.4, random_state=0)

estimator = svm.SVC(gamma='auto', C=1.0, kernel='rbf')
estimator.fit(X_train, y_train)

print("\n=== Prediction test ===")
print("Expected: " + str(y[-1:]))
result = estimator.predict(X[-1:])
print("Actual: " + str(result))

print("\n=== Cross validation results ===")
predicted = cross_val_predict(estimator, X, y, cv=5)
accuracy_score = metrics.accuracy_score(y, predicted)
print("Accuracy score: " + str(accuracy_score))

print("\n=== Test set results ===")
accuracy = estimator.score(X_test, y_test)
print("Accuracy score: " + str(accuracy))

print("\n=== Learning curve ===")
# Cross validation with 10 iterations to get smoother mean test and train
# score curves, each time with 20% data randomly selected as a validation set.
cv = ShuffleSplit(n_splits=10, test_size=0.2, random_state=0)
plot_learning_curve(estimator, X, y, cv)
