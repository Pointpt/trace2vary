# trace2vary - A Traceability Recovery Algorithm For Sotware Product Lines

## About
trace2vary is a Traceability Recovery Algorithm For Sotware Product Lines written in Python

## Methods

sgd     It refers to the Stochastic Gradient Descent method.

svm     It refers to the Support Vector Machine method.

### Files to unzip
trace2vary/projects/openldap-2.4.45/data.csv.zip
trace2vary/projects/freebsd/data.csv.zip
trace2vary/projects/netbsd/data.csv.zip
trace2vary/projects/openbsd/data.csv.zip

## How to use
You must comply with the following command syntax:

        python3 trace2vary.py <options> [-only-sgd]

        <options>
                -p      Apply pre-processing for the project to be analyzed.
                -fit    Fit the machine learning model considering the training set. It requires the [method] argument.
                -tr     Recover the traces for the analyzed project.
                -cv     Performs the commonality and variability (C & V) analysis for the stated products'projects.

        [-only-sgd]
                It runs only the Stochastic Gradient Descent method for the requested task.
                This is not applied to the -p and -cv options, since they do not use a machine learning algorithm to accomplish the task.

        Examples:
                python3 trace2vary.py -p
                python3 trace2vary.py -p -only-sgd
                python3 trace2vary.py -fit
                python3 trace2vary.py -fit -only-sgd
                python3 trace2vary.py -tr
                python3 trace2vary.py -tr -only-sgd
                python3 trace2vary.py -cv

### Required packages
nltk

pandas

numpy

scipy

scikit-learn

matplotlib

auto-sklearn