# trace2vary - A Traceability Recovery Algorithm For Sotware Product Lines

## About
trace2vary is a Traceability Recovery Algorithm For Sotware Product Lines written in Python

## Methods

SGD: it refers to the Stochastic Gradient Descent method.

AutoML: it refers to the automatic identification of the machine learning method.

### Files to unzip
projects/openldap-2.4.45/data.csv.zip

projects/freebsd/data.csv.zip

projects/netbsd/data.csv.zip

projects/openbsd/data.csv.zip

## How to use
You must comply with the following command syntax:

        python3 trace2vary.py <options> [-default]

        <options>
                -p      Apply pre-processing for the project to be analyzed.
                -fit    Fit the machine learning model considering the training set. It requires the [method] argument.
                -tr     Recovers the traces for the analyzed project.
                -cv     Performs the commonality and variability (C & V) analysis for the stated products'projects.
                -vis    Starts the visualization client for the trace2vary output file.
                -core   Runs the -tr (with the default method), -cv and -vis tasks in a sequential way.
                -pre    Prepares trace2vary for the core tasks, by running the -p and -fit tasks with the default method.

        [-default]
                It runs only the default method, Stochastic Gradient Descent, for the requested task.
                This is only applied to the -fit and -tr options,
                since they do not use a machine learning algorithm to accomplish the task.

        Examples:
                python3 trace2vary.py -core
                python3 trace2vary.py -pre
                python3 trace2vary.py -p
                python3 trace2vary.py -fit
                python3 trace2vary.py -fit -default
                python3 trace2vary.py -tr
                python3 trace2vary.py -tr -default
                python3 trace2vary.py -cv
                python3 trace2vary.py -vis

### Required packages
nltk, pandas, numpy, scipy, scikit-learn, auto_ml, bokeh, pscript