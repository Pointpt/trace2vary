from difflib import SequenceMatcher


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
