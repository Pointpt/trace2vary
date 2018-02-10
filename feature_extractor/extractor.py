# -*- coding: utf-8 -*-
import glob
import os
from xml.dom import minidom

"""SPLTrac: SPL Traceability Experimental Suite

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""


class FeatureExtractor:
    """This class is responsible for extracting the features according to the specific SPL implementation technique:
    FeatureHouse, CIDE, Antenna, AHEAD, or HyperJ
    """

    def __init__(self, project, method):
        self.project = project
        self.method = method
        self.features_dictionary = {}

    def analyze_project(self):
        if self.method == 'featurehouse':
            self.extract_feature_house_features()
        elif self.method == 'cide':
            self.extract_cide_features()
        elif self.method == 'antenna':
            self.extract_antenna_features()
        elif self.method == 'ahead':
            self.extract_ahead_features()
        elif self.method == 'hyperj':
            self.extract_hyper_j_features()
        else:
            self.extract_preprocessor_features()
        # else:  # features for the test project called Test-project
            # self.features_dictionary['to'] = ('to',)
            # self.features_dictionary['da'] = ('da',)

        self.extract_thesaurus()

        # removing base features (if available)
        if 'base' in self.features_dictionary:
            del self.features_dictionary['base']

        # print('Extracted features: ' + str(self.features_dictionary))

    def extract_feature_house_features(self):
        """Identifies features from the FeatureHouse projects."""
        exp_files_list = glob.glob(self.project + '/**/*.exp', recursive=True)
        if exp_files_list:
            self.read_features_plain_list_file(exp_files_list[0])
        else:
            features_files_list = glob.glob(self.project + '/**/*All.features', recursive=True)
            if features_files_list:
                self.read_features_plain_list_file(features_files_list[0])
            else:
                self.read_model_xml()

    def extract_cide_features(self):
        """Identifies features from the CIDE projects."""
        document = minidom.parse(self.project + '/model.colors')
        feature_list = document.getElementsByTagName('featureattr')
        for element in feature_list:
            if 'name' in element.attributes and 'id' in element.attributes:
                feature_name = element.attributes['name'].value
                self.features_dictionary[feature_name.lower()] = (feature_name.lower(),)

    def extract_ahead_features(self):
        """Identifies features from the AHEAD projects."""
        self.read_model_xml()

    def extract_antenna_features(self):
        """Identifies features from the Antenna projects."""
        self.read_model_xml()

    def extract_hyper_j_features(self):
        """Identifies features from the HyperJ projects."""
        feature_folder_list = glob.glob(self.project + '/**/src/feature', recursive=True)
        if feature_folder_list:
            for folder_name in os.walk(feature_folder_list[0]):
                if folder_name:
                    feature_name = folder_name[0].split('/')[-1]
                    self.features_dictionary[feature_name.lower()] = (feature_name.lower(),)

    def extract_preprocessor_features(self):
        """Identifies features from thesaurus of preprocessor projects.
            The features were extracted using the CPPStats tool (https://github.com/clhunsen/cppstats).
        """
        try:
            thesaurus_file = open(self.project + '/thesaurus.dat', "r")
            for line in thesaurus_file:
                terms = line.strip().split(':')
                if terms:
                    key_feature = terms[0]
                    self.features_dictionary[key_feature.lower()] = (key_feature.lower(),)
            thesaurus_file.close()
        except FileNotFoundError:
            print('No thesaurus available')

    def read_features_plain_list_file(self, file_name):
        """Method used for FeatureHouse projects to support reading .exp files."""
        features_file = open(file_name, "r")
        for feature in [line.strip() for line in features_file]:
            if feature:
                self.features_dictionary[feature.lower()] = (feature.lower(),)
        features_file.close()

    def read_model_xml(self):
        """Method used for AHEAD/Antenna projects to support reading model.xml files."""
        xml_files_list = glob.glob(self.project + '/**/*model.xml', recursive=True)
        if xml_files_list:
            self.extract_features_into_xml(xml_files_list[0])

    def extract_features_into_xml(self, file_name):
        """Method used for reading XML tags into model.xml files."""
        document = minidom.parse(file_name)
        feature_list = document.getElementsByTagName('feature')
        and_list = document.getElementsByTagName('and')
        or_list = document.getElementsByTagName('or')
        alt_list = document.getElementsByTagName('alt')
        full_list = feature_list + and_list + or_list + alt_list
        for element in full_list:
            if 'abstract' not in element.attributes:
                feature = element.attributes['name'].value
                self.features_dictionary[feature.lower()] = (feature.lower(),)
        # print(self.features_dictionary)

    def extract_thesaurus(self):
        """Method that reads the thesaurus.dat file to identify synonyms for each feature (if available)."""
        try:
            thesaurus_file = open(self.project + '/thesaurus.dat', "r")
            for line in thesaurus_file:
                terms = line.strip().split(':')
                if terms:
                    key_feature = terms[0]
                    synonyms = terms[-1].split(',')
                    for feature in synonyms:
                        if key_feature in self.features_dictionary:
                            self.features_dictionary[key_feature.lower()] += (feature.lower(),)
            thesaurus_file.close()
        except FileNotFoundError:
            print('No thesaurus available')

    def get_features_dictionary(self):
        return self.features_dictionary
