# trace2vary - An Algorithm to Recover Feature-Code Traceability and Variability in Variant-Rich Systems

## About

*trace2vary* is a traceability recovery algorithm for variant-rich systems written in Python.
It takes machine learning methods to improve the precision and recall during the indication of relevance between
a feature and a source code file.

## Methods

*trace2vary* has two machine learning algorithm options when recovering feature-source code file links:

- [SGD](http://scikit-learn.org/stable/modules/sgd.html): it refers to the Stochastic Gradient Descent method.
- [AutoML](http://auto-ml.readthedocs.io/en/latest/): it refers to the automatic identification of the machine learning method.

## How to use

### Dataset preparation

Before running the *trace2vary* command, **you have to unzip** the following files
(they are compressed due to GitHub file size constraints):

- projects/openldap-2.4.45/data.csv.zip
- projects/freebsd/data.csv.zip
- projects/netbsd/data.csv.zip
- projects/openbsd/data.csv.zip

In addition, **the following python packages have to be installed**:

- [nltk](https://www.nltk.org/install.html)
- [pandas](https://pandas.pydata.org/pandas-docs/stable/install.html)
- [numpy](https://pypi.org/project/numpy/)
- [scipy](https://www.scipy.org/install.html)
- [scikit-learn](http://scikit-learn.org/stable/install.html)
- [auto_ml](https://pypi.org/project/auto_ml/)
- [bokeh](https://bokeh.pydata.org/en/latest/docs/installation.html)
- [python-Levenshtein](https://pypi.org/project/python-Levenshtein/)

### Command syntax

You must comply with the following command syntax:

```
python3 trace2vary.py <options> [-default]

<options>
        -p      Apply pre-processing for the project to be analyzed.
        -fit    Fit the machine learning model considering the training set. It requires the [method] argument.
        -tr     Recovers the traces for the analyzed project.
        -cv     Performs the commonality and variability (C & V) analysis for the stated products'projects.
        -vis    Starts the visualization client for the *trace2vary* output file.
        -core   Runs the -tr (with the default method), -cv and -vis tasks in a sequential way.
        -pre    Prepares *trace2vary* for the core tasks, running the -p and -fit tasks with the default method.

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
```