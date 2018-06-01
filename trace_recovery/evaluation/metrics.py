# -*- coding: utf-8 -*-

"""trace2vary: An Algorithm to Recover Feature-Code Traceability and Variability

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""


class ProjectMethodMetricsResult:
    """This class provides data structure and algorithm for calculation of precision, recall, F-measure
    (F1 measure - harmonic mean) and performance metrics for a given project.
    """

    def __init__(self, project, true_traces, method_name, method_traces, performance):
        self.project = project
        self.true_traces = true_traces
        self.method_name = method_name
        self.method_traces = method_traces
        self.performance = performance

        self.precision_per_feature = {}
        self.precision = 0.0
        self.recall_per_feature = {}
        self.recall = 0.0
        self.f_measure = 0.0
        self.calculate_metric_results()

    def calculate_metric_results(self):
        """
        It performs the calculation of metrics for the project.
        """

        acum_precision = 0.0
        acum_recall = 0.0
        n = 0
        for (feature, method_documents_tuple) in self.method_traces.items():
            if feature in self.true_traces:
                n += 1

                intersection_set = set(method_documents_tuple) & set(self.true_traces[feature])

                # calculating precision
                if method_documents_tuple:
                    self.precision_per_feature[feature] = len(intersection_set) / len(method_documents_tuple)
                else:
                    self.precision_per_feature[feature] = 0
                acum_precision += self.precision_per_feature[feature]

                # calculating recall
                if self.true_traces[feature]:
                    self.recall_per_feature[feature] = len(intersection_set) / len(self.true_traces[feature])
                else:
                    self.recall_per_feature[feature] = 0
                acum_recall += self.recall_per_feature[feature]

        if n != 0:
            self.precision = acum_precision / n
            self.recall = acum_recall / n
        else:
            self.precision = 0
            self.recall = 0

        if self.recall != 0 and self.precision != 0:
            self.f_measure = (2 * self.precision * self.recall) / (self.precision + self.recall)
        else:
            self.f_measure = 0



