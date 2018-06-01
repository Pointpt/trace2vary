# -*- coding: utf-8 -*-
import numpy

"""trace2vary: An Algorithm to Recover Feature-Code Traceability and Variability

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""


def bm25_calculation(pre_processor, features, document, k1_const, b_const):
    """
    This variability_impl_technology calculates the similarity of every document
    for a given feature (and related synonyms).
    :param pre_processor: preprocessed data from the project
    :param features: set of feature and its synonyms to be analyzed
    :param document: document to be analyzed
    :param k1_const: k1 constant used for the BM25 method
    :param b_const: B constant used for the BM25 method
    :return: similarity value between feature and document
    """

    avg_document_length = get_avg_document_len(pre_processor)

    similarity_value = 0.0
    for (term, index_by_term) in pre_processor.get_inverted_index().items():
        if term in features and document in index_by_term:
            document_term_frequency = index_by_term[document].frequency
            bm25_num = (k1_const + 1) * document_term_frequency
            bm25_den = k1_const * \
                       ((1 - b_const) + b_const * (pre_processor.get_document_length(document) /
                                                   avg_document_length)) + document_term_frequency
            bm25_value = bm25_num / bm25_den
            similarity_value += bm25_value * \
                                numpy.math.log(pre_processor.get_num_files()
                                               / pre_processor.get_docs_per_term(term), 2)

    return similarity_value


def get_avg_document_len(pre_processor):
    """
    It calculates the average document size considering the number of terms.
    :param pre_processor: preprocessed data from the project
    :return: resulting average value
    """
    acum = 0
    for (doc, length) in pre_processor.get_documents().items():
        acum += length
    if pre_processor.get_num_files() != 0:
        return acum / pre_processor.get_num_files()
    else:
        return 0
