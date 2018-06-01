import os.path
import Levenshtein

"""trace2vary: An Algorithm to Recover Feature-Code Traceability and Variability

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""


def calculate_file_differences(file, pairs_of_files, files_content_dictionary,
                               diff_ratios_dictionary, levenshtein_dictionary):
    """
    It calculates the diff ratio and Levenshtein distance for a set containing pairs of files.
    :param file: unique file name to be analyzed
    :param pairs_of_files: paths for the analyzed file in different products
    :param files_content_dictionary: data structure to store the file content
    :param diff_ratios_dictionary: data structure to store diff ratios
    :param levenshtein_dictionary: data structure to store Levenshtein distance values
    """
    if len(pairs_of_files) > 0:
        total_ratio = 0
        total_levenshtein = 0
        for file_name_pair in pairs_of_files:
            first_file = files_content_dictionary[file_name_pair[0]]
            second_file = files_content_dictionary[file_name_pair[1]]
            total_ratio += Levenshtein.ratio(first_file, second_file)
            total_levenshtein += Levenshtein.distance(first_file, second_file)
        diff_ratios_dictionary[file] = total_ratio / len(pairs_of_files)
        levenshtein_dictionary[file] = total_levenshtein / len(pairs_of_files)
    else:
        diff_ratios_dictionary[file] = -1
        levenshtein_dictionary[file] = -1


def read_files_content(products_files_names, files_content_dictionary):
    """
    It stores the files' contents in a dictionary, avoiding reading a file content twice.
    :param products_files_names: list of files to read content
    :param files_content_dictionary: data structure to store the file content
    """

    for file_name in products_files_names:
        if file_name not in files_content_dictionary.keys():
            try:
                file_content = open(file_name, 'r')
                files_content_dictionary[file_name] = file_content.read()
                file_content.close()
            except UnicodeDecodeError:
                file_content = open(file_name, 'r', encoding='ISO-8859-1')
                files_content_dictionary[file_name] = file_content.read()
                file_content.close()


def get_valid_files(projects_base_path, products, file):
    """
    It returns a list with all valid files.
    :param projects_base_path: base path to investigate if the file exists
    :param products: list of potential products to have the analyzed file
    :param file: file name to be analyzed
    :return: list of valid files
    """
    valid_files = []
    for product in products:
        file_name = projects_base_path + product + '/' + file
        if os.path.isfile(file_name):
            valid_files.append(file_name)
    return valid_files
