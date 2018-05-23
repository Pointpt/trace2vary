# -*- coding: utf-8 -*-
from trace_recovery.evaluation.metrics import ProjectMethodMetricsResult
import datetime
import csv
import os

"""SPLTrac: SPL Traceability Experimental Suite

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""


class ProjectResults:
    """This data structure organizes the IR variability_impl_technology results per project storing the following data:
    project language, project LOC, feature-to-code true traces, and dictionary of results per IR variability_impl_technology
    """
    pass


class EvaluationResults:
    """This class consolidates all IR methods results of all analyzed projects and exports it to a CSV file.
    In addition, it creates R scripts ready to provide statistic results regarding the following metrics:
    recall, precision, F-measure and performance. 
    """

    def __init__(self):
        self.project_results = {}

    def add_project_input_data(self, project, variability_impl_technology, language, number_of_files, loc, true_traces):
        """It includes the project information to the project results dictionary."""
        project_result = ProjectResults()
        project_result.variability_impl_technology = variability_impl_technology
        project_result.language = language
        project_result.number_of_files = number_of_files
        project_result.loc = loc
        project_result.true_traces = true_traces
        project_result.method_results = {}
        self.project_results[project] = project_result

    def add_method_results(self, project, method_name, method_traces, performance):
        """It adds the results of a specific IR variability_impl_technology to a given project."""
        method_result = ProjectMethodMetricsResult(
            project,
            self.project_results[project].true_traces,
            method_name,
            method_traces,
            performance
        )
        self.project_results[project].method_results[method_name] = method_result

    def export_results(self):
        """This variability_impl_technology generates the CSV and R script files."""
        date_time_str = datetime.datetime.now().strftime('%Y-%m-%d_%Hh%Mm')
        output_file_str = date_time_str + '_output.csv'
        with open('trace_recovery/results/' + output_file_str, 'w') as csv_file:
            output_data_writer = csv.writer(csv_file, quoting=csv.QUOTE_MINIMAL)
            output_data_writer.writerow(
                [
                    'project',
                    'language',
                    'files',
                    'loc',
                    'features',
                    'variability_impl_technology',
                    'method',
                    'recall',
                    'precision',
                    'fmeasure',
                    'performance'
                ]
            )
            for (project, project_result) in self.project_results.items():
                for (method, method_result) in project_result.method_results.items():
                    output_data_writer.writerow(
                        [
                            project.split('/')[-1],
                            project_result.language,
                            project_result.number_of_files,
                            project_result.loc,
                            len(project_result.true_traces.keys()),
                            project_result.variability_impl_technology,
                            method, method_result.recall,
                            method_result.precision,
                            method_result.f_measure,
                            method_result.performance
                        ]
                    )
            EvaluationResults.write_r_file(output_file_str, date_time_str, 'precisionrecall')
            EvaluationResults.write_r_file(output_file_str, date_time_str, 'performanceavg')
            EvaluationResults.write_r_file(output_file_str, date_time_str, 'fmeasure')
            EvaluationResults.write_r_file(output_file_str, date_time_str, 'precision')
            EvaluationResults.write_r_file(output_file_str, date_time_str, 'recall')
            EvaluationResults.write_r_file(output_file_str, date_time_str, 'variances')

    @staticmethod
    def write_r_file(output_file_str, date_time_str, file_type):
        """Method which replaces the strings from a template script, putting the correct data."""
        with open('trace_recovery/results/templates/script_template_' + file_type + '.R', 'r') as template_script_file:
            script_data = template_script_file.read()
            # print(script_data)
            script_data = script_data.replace('<directory>', os.getcwd() + '/trace_recovery/results/')
            script_data = script_data.replace('<output_file_name>', output_file_str)
            script_data = script_data.replace('<pdf_image_file_name>', date_time_str + '_' + file_type + '_chart')

            resulting_script_file = open('trace_recovery/results/' + date_time_str + '_' + file_type + '_script.R', "w")
            resulting_script_file.write(script_data)
            resulting_script_file.close()

