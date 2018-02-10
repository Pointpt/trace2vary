# -*- coding: utf-8 -*-
import numpy
import threading
import time

"""SPLTrac: SPL Traceability Experimental Suite

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""


def extended_boolean_calculation(pre_processor, features, document):
    """This variability_impl_technology calculates the similarity of every document
    for a given feature (and related synonyms)."""

    # reading p-norm value
    with open('../information_retrieval/extended_boolean_p_norm.dat', "r") as p_norm_file:
        p_norm = int(p_norm_file.readline())
        p_norm_file.close()

        maximum_idf = get_maximum_idf(pre_processor)

        sum_query_document_weights = 0.0
        maximum_frequency = get_maximum_frequency(pre_processor, document, features)

        for (term, index_by_term) in pre_processor.get_inverted_index().items():
            if term in features and document in index_by_term:
                document_weight = index_by_term[document].frequency / maximum_frequency
                document_term_frequency = pre_processor.get_docs_per_term(term)
                query_weight = \
                    numpy.math.log((pre_processor.get_num_files() / document_term_frequency), 2) / maximum_idf
                sum_query_document_weights += numpy.power(document_weight, p_norm) * \
                                              numpy.power(query_weight, p_norm)

        numerator = sum_query_document_weights / len(features)
        if len(features) != 0 and p_norm != 0 and numerator > 0:
            return numpy.power(numerator, 1 / p_norm)
        else:
            return 0


def get_maximum_frequency(pre_processor, document, features):
    """This variability_impl_technology identifies the maximum TF value for a given document."""
    maximum_frequency = 0.0
    for (term, index_by_term) in pre_processor.get_inverted_index().items():
        if term in features and document in index_by_term:
            frequency = index_by_term[document].frequency
            if maximum_frequency < frequency:
                maximum_frequency = frequency
    return maximum_frequency


def get_maximum_idf(pre_processor):
    """This variability_impl_technology identifies the maximum IDF value for the project."""
    maximum_idf = 0.0
    for (term, index_by_term) in pre_processor.get_inverted_index().items():
        number_of_documents_for_a_term = len(index_by_term.keys())
        idf = numpy.math.log((pre_processor.get_num_files() / number_of_documents_for_a_term), 2)
        if maximum_idf < idf:
            maximum_idf = idf
    return maximum_idf
