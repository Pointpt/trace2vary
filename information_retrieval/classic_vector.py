# -*- coding: utf-8 -*-
import numpy

"""SPLTrac: SPL Traceability Experimental Suite

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""


def classic_vector_calculation(pre_processor, features, document):
    """This variability_impl_technology calculates the similarity of a document
    for a given feature (and related synonyms)."""

    sum_query_document_weights = 0.0
    sum_tf = 0.0
    sum_idf = 0.0

    for (term, index_by_term) in pre_processor.get_inverted_index().items():
        if term in features and document in index_by_term:
            index_by_term = pre_processor.get_inverted_index()[term]
            term_document_ocurrences = pre_processor.get_docs_per_term(term)
            idf = numpy.math.log((pre_processor.get_num_files() / term_document_ocurrences), 2)
            sum_idf += numpy.square(idf)
            tf = 1 + numpy.math.log(index_by_term[document].frequency, 2)
            sum_tf += numpy.square(tf)
            sum_query_document_weights += tf * idf

    if sum_tf != 0 and sum_idf != 0:
        return sum_query_document_weights / (numpy.sqrt(sum_idf) * numpy.sqrt(sum_tf))
    else:
        return 0
