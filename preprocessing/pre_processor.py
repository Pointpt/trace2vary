# -*- coding: utf-8 -*-
from nltk.tokenize import RegexpTokenizer
from collections import Counter
import glob
import json

"""SPLTrac: SPL Traceability Experimental Suite

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""


class DocumentDataByTerm:
    """Objects from this class stores the frequency and weight of a term-document element"""
    pass


class SPLProjectPreProcessor:
    """This class performs the pre-processing step of the SPL projects.
    
    It identifies the valid source code files for analysis, extracts the terms of the document (removing terms such as
    reserved words of the language), and count the terms frequency per file, storing it in a proper data structure.
    It also provides methods with faster response time to support the IR methods regarding specific project data.
    """

    def __init__(self, project, language, features_dictionary, remove_ifdefs):

        self.features_dictionary = features_dictionary
        self.remove_ifdefs = remove_ifdefs

        self.num_files = 0
        self.stop_words = set()
        self.inverted_index = {}
        self.index_terms = set()
        self.documents = {}
        self.generate_index(project, language)

    def generate_index(self, project, language):
        """It builds the index for the SPL project files (documents).

        The variability_impl_technology identifies all valid files to be processed (considering the programming language)
        and requests the processing of all term frequencies per document.
        """

        stop_word_file = open('preprocessing/stopwords_' + language + '.dat', "r")
        self.stop_words = set([line.strip() for line in stop_word_file])
        stop_word_file.close()

        if language == 'c':
            self.analyze_term_document_frequency(project, '.c')
            self.analyze_term_document_frequency(project, '.h')
        elif language == 'java':
            self.analyze_term_document_frequency(project, '.java')
            self.analyze_term_document_frequency(project, '.jak')
            self.analyze_term_document_frequency(project, '.aj')
        elif language == 'cpp':
            self.analyze_term_document_frequency(project, '.cpp')
            self.analyze_term_document_frequency(project, '.h')
        elif language == 'cs':
            self.analyze_term_document_frequency(project, '.cs')
        elif language == 'python':
            self.analyze_term_document_frequency(project, '.py')
        elif language == 'haskell':
            self.analyze_term_document_frequency(project, '.hs')

    def analyze_term_document_frequency(self, project, file_extension):
        """This variability_impl_technology builds the inverted index for terms and related documents.

           It is responsible for creating the data structure to store term-document data
           and count the frequencies of terms per document.
        """
        for file_name in glob.iglob(project + '/**/*' + file_extension, recursive=True):
            self.num_files += 1

            # reading file
            try:
                source_file = open(file_name, 'r')
                file_content = source_file.read()
                source_file.close()
            except UnicodeDecodeError:
                source_file = open(file_name, 'r', encoding="ISO-8859-1")
                file_content = source_file.read()
            source_file.close()

            if self.remove_ifdefs:
                # removing ifdef directives, if available
                lines = file_content.splitlines()
                for line in lines:
                    if '#if' in line:
                        lines.remove(line)
                file_content = '\n'.join(lines)

            tokenizer = RegexpTokenizer(r'[\w\']+')  # get tokens, removing punctuation and other single characters
            tokens = tokenizer.tokenize(file_content.lower())  # get tokens in lower case
            self.documents[file_name] = len(tokens)
            # print(tokens)

            # counting frequencies for a specific file
            file_counter = Counter(tokens)

            for (term, frequency) in file_counter.most_common():
                self.index_terms.add(term)
                if frequency > 0 and term not in self.stop_words:
                    aux_index = {}
                    document_data_by_term = DocumentDataByTerm()
                    document_data_by_term.frequency = frequency
                    document_data_by_term.weight = 0
                    aux_index[file_name] = document_data_by_term
                    try:
                        self.inverted_index[term].update(aux_index)
                    except KeyError:
                        self.inverted_index[term] = aux_index

            for (key, features_tuple) in self.features_dictionary.items():
                for feature in features_tuple:
                    feature_frequency = 0
                    if feature not in file_counter.most_common() and feature not in self.stop_words:
                        for token in tokens:
                            if feature in token:
                                feature_frequency += 1
                        if feature_frequency > 0:
                            aux_index = {}
                            document_data_by_term = DocumentDataByTerm()
                            document_data_by_term.frequency = feature_frequency
                            document_data_by_term.weight = 0
                            aux_index[file_name] = document_data_by_term
                            try:
                                self.inverted_index[feature].update(aux_index)
                            except KeyError:
                                self.inverted_index[feature] = aux_index

    def get_docs_per_term(self, term):
        doc_term_dictionary = self.inverted_index[term]
        return len(doc_term_dictionary.keys())

    def get_inverted_index(self):
        return self.inverted_index

    def get_num_files(self):
        return self.num_files

    def get_stop_words(self):
        return self.stop_words

    def get_index_terms(self):
        return self.index_terms

    def get_documents(self):
        return self.documents

    def get_document_length(self, document):
        return self.documents[document]