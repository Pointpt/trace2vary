# -*- coding: utf-8 -*-
import numpy

"""trace2vary: An Algorithm to Recover Feature-Code Traceability and Variability

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""


def calculate_tfidf_weights(pre_processor):
    """Calculate the TF-IDF for all the features (and related synonyms).

    Foundations of the most popular term weighting scheme in IR tf-idf variability_impl_technology with log normalization
    and inverse frequency. The tf-idf weighting scheme used is (1 + log fi,j) ∗ log N / ni
    :param pre_processor: preprocessed data from the project
    """

    for (term, documents_dictionary) in pre_processor.get_inverted_index().items():
        term_document_ocurrences = pre_processor.get_docs_per_term(term)

        for document_data in documents_dictionary.values():
            tfidf_weight = (1 + numpy.math.log(document_data.frequency, 2)) \
                           * numpy.math.log((pre_processor.get_num_files() / term_document_ocurrences), 2)
            document_data.weight = tfidf_weight


def tfidf_resulting_value(pre_processor, features, document):
    """
    Method used for tests to check the similarity value of documents to the respective features.
    :param pre_processor: preprocessed data from the project
    :param features: set of feature and its synonyms to be analyzed
    :param document: document to be analyzed
    :return: similarity value between feature and document
    """

    tfidf = 0
    for feature in features:
        if feature in pre_processor.get_inverted_index():
            documents_dictionary = pre_processor.get_inverted_index()[feature]
            if document in documents_dictionary:
                tfidf += documents_dictionary[document].weight

    return tfidf


def document_frequency_value(pre_processor, features, document):
    """
    Method used for tests to check the similarity value of documents to the respective features.
    :param pre_processor: preprocessed data from the project
    :param features: set of feature and its synonyms to be analyzed
    :param document: document to be analyzed
    :return: term frequency value
    """

    tf = 0
    for feature in features:
        if feature in pre_processor.get_inverted_index():
            documents_dictionary = pre_processor.get_inverted_index()[feature]
            if document in documents_dictionary:
                tf += documents_dictionary[document].frequency

    return tf
