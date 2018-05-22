import config
import json
from commonality_and_variability.cv_utils \
    import get_all_features, identify_products_per_feature, set_file_variability_type_per_feature, apply_diff
# edit distance described by Levenshtein


def compare_products():

    print('===== COMMONALITY AND VARIABILITY ANALYSIS =====')

    products_traces_dictionary = dict()
    trace2vary_results_dictionary_per_feature = dict()

    with open(config.test_set_file, 'r') as products_file:
        print('1/6 - Reading products\' traces')
        projects_base_path = products_file.readline().strip('\n')
        for line in products_file:
            (product, language, variability_impl_technology, files, loc, features) = line.split()
            try:
                with open(projects_base_path + product + '/traces.json', 'r') as traces_file:
                    traces = json.load(traces_file)
                    products_traces_dictionary[product] = traces
                    print('Product: ' + product + ' OK')
            except FileNotFoundError:
                print('Product: ' + product + ' [ERROR] traces files not found')

        # Traces mocking
        # products_traces_dictionary = {
        #     'prod1': {
        #         'feature1': ['file/f11', 'file/f12', 'file/f13', 'file/f14', 'file/f15', 'file/f16', 'file/f17'],
        #         'feature2': ['file/f21'],
        #         'feature3': ['file/f31'],
        #         'feature4': ['file/f41']
        #     },
        #     'prod2': {
        #         'feature1': ['file/f11', 'file/f12', 'file/f13', 'file/f15', 'file/f16'],
        #         'feature2': ['file/f21'],
        #         'feature3': ['file/f31'],
        #         'feature4': ['file/f41']
        #     },
        #     'prod3': {
        #         'feature1': ['file/f11', 'file/f12', 'file/f13'],
        #         'feature2': ['file/f21'],
        #         'feature3': ['file/f33']
        #     }
        # }

        print('2/6 - Gathering the full set of features')
        features_set = get_all_features(products_traces_dictionary)

        print('3/6 - Identifying products for each feature')
        identify_products_per_feature(
            features_set, products_traces_dictionary, trace2vary_results_dictionary_per_feature
        )

        print('4/6 - Identifying common, shared and specific products\' files for each feature')
        set_file_variability_type_per_feature(
            products_traces_dictionary, trace2vary_results_dictionary_per_feature
        )

        print('5/6 - Analyzing differences between common and shared files through diff')
        apply_diff(projects_base_path, trace2vary_results_dictionary_per_feature)

        print('6/6 - Exporting results to a JSON file')
        print_trace2vary_results(trace2vary_results_dictionary_per_feature)


def print_trace2vary_results(trace2vary_results):
    for (key, obj) in trace2vary_results.items():
        print('\nFeature: ' + key)
        if obj.type == config.mandatory_str:
            print('Type: ' + obj.type)
        else:
            print('Type: ' + obj.type + ' / Products: ' + str(obj.products))
        print('All files: ' + str(obj.all_files))
        print('Common files: ' + str(obj.common_files))
        print('Shared files: ' + str(obj.shared_files))
        print('Specific files: ' + str(obj.specific_files))
        print('Common files\' ratios:')
        for (file, ratio) in obj.common_files_diff_ratios.items():
            if ratio != -1:
                print('File: ' + file + ' / Diff ratio: ' + str(ratio))
        print('Shared files\' ratios:')
        for (file, ratio) in obj.shared_files_diff_ratios.items():
            if ratio != -1:
                print('File: ' + file + ' / Diff ratio: ' + str(ratio))

