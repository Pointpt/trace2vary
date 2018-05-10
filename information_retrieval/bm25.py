# -*- coding: utf-8 -*-
import numpy

"""SPLTrac: SPL Traceability Experimental Suite

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""


def bm25_calculation(pre_processor, features, document, k1_const, b_const):
    """This variability_impl_technology calculates the similarity of every document
    for a given feature (and related synonyms)."""

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
    """It calculates the average document size considering the number of terms."""
    acum = 0
    for (doc, length) in pre_processor.get_documents().items():
        acum += length
    if pre_processor.get_num_files() != 0:
        return acum / pre_processor.get_num_files()
    else:
        return 0
