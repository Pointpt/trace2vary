import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn import preprocessing
import autosklearn.classification

training_data_frame = pd.read_csv("../projects/training/full_training_set.csv")

features_data_frame = training_data_frame.drop(['Feature', 'Document', 'Result'], 1)
features_matrix = features_data_frame.as_matrix()
X = preprocessing.normalize(features_matrix)  # normalizing features' values

y = training_data_frame['Result'].values

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.4, random_state=0)

cls = autosklearn.classification.AutoSklearnClassifier()
cls.fit(X_train, y_train)
predictions = cls.predict(X_test)
