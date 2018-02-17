# -*- coding: utf-8 -*-
from multiprocessing.pool import ThreadPool
import pandas as pd
from feature_extractor.extractor import FeatureExtractor
from preprocessing.pre_processor import SPLProjectPreProcessor
from information_retrieval.tfidf import *
from information_retrieval.classic_vector import classic_vector_calculation
from information_retrieval.neural_networks import *
from information_retrieval.bm25 import bm25_calculation
from information_retrieval.extended_boolean import extended_boolean_calculation

"""SPLTrac: SPL Traceability Experimental Suite

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""


def extract_true_traces(project_path):
    """It extracts the true traces from the traceability_oracle.dat file."""
    true_traces = {}

    with open(project_path + '/traceability_oracle.dat', "r") as oracle_file:
        for oracle_file_line in oracle_file:
            if ':' in oracle_file_line:
                terms = oracle_file_line.strip().split(':')
                if terms[-1] is 'none':
                    true_traces[key_feature] += ()
                else:
                    key_feature = terms[0]
                    synonyms = terms[-1].split(',')
                    for document in synonyms:
                        document = project_path + '/' + document
                        if key_feature in true_traces:
                            true_traces[key_feature] += (document,)
                        else:
                            true_traces[key_feature] = (document,)

    return true_traces


pass


class ProjectAnalysis:

    def __init__(self, project, language, variability_impl_technology, loc, data):
        self.project = project
        self.language = language
        self.variability_impl_technology = variability_impl_technology
        self.loc = loc
        self.data = data

    def run(self):

        data_frame = pd.DataFrame()

        with open('../information_retrieval/bm25_constants.dat', "r") as bm25_constants_file:

            # Reading BM25 method constants
            k1_const = int(bm25_constants_file.readline())
            b_const = float(bm25_constants_file.readline())

            # EXECUTION OF THE INFORMATION RETRIEVAL ALGORITHMS
            print('\n\n\nProject: ' + self.project)
            print('Language: ' + self.language.upper())
            print('Variability realization technology: ' + self.variability_impl_technology.upper())

            print('Step 1: extracting features...')
            feature_extractor = FeatureExtractor(self.project, self.variability_impl_technology)
            feature_extractor.analyze_project()
            features_dictionary = feature_extractor.get_features_dictionary()

            print('Step 2: reading project true traces...')
            traces = extract_true_traces(self.project)

            print('Step 3: processing project...')
            print('Progress: 0%', end="", flush=True)

            # Preprocessor and CIDE projects are the ones which implement ifdef conditional compilation directives
            remove_ifdefs = False
            if self.variability_impl_technology == 'preprocessor' or self.variability_impl_technology == 'cide':
                remove_ifdefs = True
            pre_processor = SPLProjectPreProcessor(self.project, self.language, features_dictionary, remove_ifdefs)

            # TF-IDF calculation
            calculate_tfidf_weights(pre_processor)

            features_total = len(features_dictionary)
            features_counter = 1

            for (feature_name, feature_synonyms) in features_dictionary.items():

                print('\rProgress: ' + str(round(features_counter * 100 / features_total)) + '%', end="", flush=True)

                # Building the neural network for a given feature
                neural_network = create_neural_network(pre_processor, feature_synonyms)

                for document in pre_processor.get_documents().keys():

                    pool = ThreadPool(processes=1)

                    # Frequency of the term in the document
                    document_frequency_result = pool.apply_async(
                        document_frequency_value, (pre_processor, feature_synonyms, document)
                    )

                    # TF-IDF measure
                    tfidf_result = pool.apply_async(
                        tfidf_resulting_value, (pre_processor, feature_synonyms, document)
                    )

                    # Algebraic - classic vector model
                    classic_vector_result = pool.apply_async(
                        classic_vector_calculation, (pre_processor, feature_synonyms, document)
                    )

                    # Algebraic - neural networks model
                    neural_network_result = pool.apply_async(
                        neural_network_calculation, (neural_network, document)
                    )

                    # Set theoretic - extended boolean model
                    extended_boolean_result = pool.apply_async(
                        extended_boolean_calculation, (pre_processor, feature_synonyms, document)
                    )

                    # Probabilistic - BM25 model
                    bm25_result = pool.apply_async(
                        bm25_calculation, (pre_processor, feature_synonyms, document, k1_const, b_const)
                    )

                    doc_frequency_value = document_frequency_result.get()
                    tfidf_value = tfidf_result.get()
                    classic_vector_value = classic_vector_result.get()
                    neural_network_value = neural_network_result.get()
                    extended_boolean_value = extended_boolean_result.get()
                    bm25_value = bm25_result.get()

                    traced = 0
                    if feature_name in traces and document in traces[feature_name]:
                        traced = 1

                    data_frame = data_frame.append(
                        {
                            'Feature': feature_name,
                            'Document': document,
                            'Term frequency': doc_frequency_value,
                            'TF-IDF': tfidf_value,
                            'Classic vector': classic_vector_value,
                            'Neural network': neural_network_value,
                            'Extended boolean': extended_boolean_value,
                            'BM25': bm25_value,
                            'Result': traced
                        },
                        ignore_index=True
                    )

                    # print('\n\n==============================')
                    # print('Feature and synonyms: ' + str(feature_synonyms))
                    # print('Document: ' + str(document))
                    # print('Values: [' + str(doc_frequency_value) + ', ' + str(tfidf_value) + ', '
                    #      + str(classic_vector_value) + ', ' + str(neural_network_value) + ', '
                    #      + str(extended_boolean_value) + ', ' + str(bm25_value) + ', ' + str(traced) + ']')
                    # print('==============================')

                features_counter += 1

        return data_frame