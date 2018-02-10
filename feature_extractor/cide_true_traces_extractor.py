# -*- coding: utf-8 -*-
from xml.dom import minidom
import glob

"""SPLTrac: SPL Traceability Experimental Suite

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br

This script was implemented to automatically extract the feature-to-code traces within CIDE projects.
"""

features_dictionary = {}
base_path = '../product_line_projects/'
projects = ['FAME_DBMS', 'Lampiro', 'Mobile_Media', 'Mobile_RSS_Reader', 'Prevayler', 'Pynche']

for project in projects:
    traces = {}
    document = minidom.parse(base_path + project + '/model.colors')
    feature_list = document.getElementsByTagName('featureattr')
    for element in feature_list:
        if 'name' in element.attributes and 'id' in element.attributes:
            feature_name = element.attributes['name'].value
            feature_id = int(element.attributes['id'].value)
            features_dictionary[feature_id] = feature_name.lower()

    color_list = glob.glob(base_path + project + '/**/*.color', recursive=True)
    for color_file_name in color_list:
        if '.java' in color_file_name or '.cpp' in color_file_name or '.py' in color_file_name:
            document = minidom.parse(color_file_name)
            traces_list = document.getElementsByTagName('key')
            for element in traces_list:
                if 'features' in element.attributes:
                    feature_ids = element.attributes['features'].value
                    list = feature_ids.split(',')
                    for feature_id in list:
                        id = int(feature_id)
                        if id in features_dictionary:
                            feature_name = features_dictionary[id]
                            file_name = color_file_name.replace(base_path + project, '')
                            if feature_name in traces:
                                traces[feature_name].append(file_name)
                            else:
                                traces[feature_name] = [file_name]

    with open(base_path + project + '/traceability_oracle.dat', 'w+') as true_traces_file:
        for (feature_name, files_list) in traces.items():
            str_file = feature_name + ':'
            files_set = set(files_list)
            for file_name in files_set:
                file_name = file_name[1:].replace('.color','')
                str_file += file_name + ','
            str_file += '\n'
            str_file = str_file.replace(',\n','\n')
            true_traces_file.write(str_file)

    with open(base_path + project + '/initial_thesaurus.dat', 'w+') as thesaurus_file:
        for feature_name in traces.keys():
            thesaurus_file.write(feature_name + ':\n')