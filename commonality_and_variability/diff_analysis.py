from difflib import SequenceMatcher
import os.path


def calculate_diff_ratio(file, pairs_of_files, files_content_dictionary, diff_ratios_dictionary):
    total_ratio = 0
    for file_name_pair in pairs_of_files:
        try:
            first_file = files_content_dictionary[next(iter(file_name_pair))]
            second_file = files_content_dictionary[next(iter(file_name_pair))]
            diff = SequenceMatcher(None, first_file, second_file)
            total_ratio += diff.ratio()
        except FileNotFoundError:
            total_ratio = 0
            break
    if len(pairs_of_files) > 0:
        diff_ratios_dictionary[file] = total_ratio / len(pairs_of_files)
    else:
        diff_ratios_dictionary[file] = -1


def read_files_content(products_files_names, files_content_dictionary):
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
    valid_files = []
    for product in products:
        file_name = projects_base_path + product + '/' + file
        if os.path.isfile(file_name):
            valid_files.append(file_name)
    return valid_files
