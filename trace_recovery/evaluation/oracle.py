# -*- coding: utf-8 -*-

"""trace2vary: An Algorithm to Recover Feature-Code Traceability and Variability

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""


class TraceabilityOracle:
    """The provided SPL projects already have the mapped feature-to-code traces.
    This class is provides data structure and algorithm to extract such traces called 'true traces'.
    """

    def __init__(self, base_path, project):
        self.project_path = base_path + project
        self.true_traces = {}

    def extract_true_traces(self):
        """
        It extracts the true traces from the traceability_oracle.dat file.
        :return: true traces dictionary
        """
        try:
            oracle_file = open(self.project_path + '/traceability_oracle.dat', "r")
            for line in oracle_file:
                if ':' in line:
                    terms = line.strip().split(':')
                    key_feature = terms[0]
                    if terms[-1] == 'none':
                        self.true_traces[key_feature] = ()
                    else:
                        synonyms = terms[-1].split(',')
                        for document in synonyms:
                            if key_feature in self.true_traces:
                                self.true_traces[key_feature] += (document,)
                            else:
                                self.true_traces[key_feature] = (document,)
            oracle_file.close()
        except FileNotFoundError:
            print('No oracle available')

        return self.true_traces
