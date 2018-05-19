import config
import json
# https://docs.python.org/2.7/library/difflib.html
# feature 1 - diff ratio quick_ratio()
# edit distance described by Levenshtein


class FeatureResult:
    """Description
    """
    pass


def get_all_products_file_sets(products_traces_dictionary, feature, feature_result):
    files_sets = []
    for product in feature_result.products:
        files_set = get_product_files_per_feature(products_traces_dictionary, product, feature)
        files_sets.append(files_set)
    return files_sets


def get_product_files_per_feature(products_traces_dictionary, product, feature):
    files_set = set([file.rstrip('/') for file in products_traces_dictionary[product][feature]])
    return files_set


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

        # products_traces_dictionary = {
            # 'prod1': {
                # 'feature1': ['file/f11', 'file/f12', 'file/f14'],
                # 'feature2': ['file/f21'],
                # 'feature3': ['file/f31'],
                # 'feature4': ['file/f41']
            # },
            # 'prod2': {
                # 'feature1': ['file/f11', 'file/f12', 'file/f15'],
                # 'feature2': ['file/f21'],
                # 'feature3': ['file/f31'],
                # 'feature4': ['file/f41']
            # },
            # 'prod3': {
                # 'feature1': ['file/f11', 'file/f13'],
                # 'feature2': ['file/f21'],
                # 'feature3': ['file/f33']
            # }
        # }

        print('2/6 - Gathering the full set of features')
        features_set = set()
        for product in products_traces_dictionary.keys():
            product_features = set(products_traces_dictionary[product].keys())
            features_set = features_set.union(product_features)

        print('3/6 - Identifying products for each feature')
        for feature in features_set:
            feature_result = FeatureResult()
            feature_result.products = []
            for (product, traces) in products_traces_dictionary.items():
                if feature in traces.keys():
                    feature_result.products.append(product)
            if len(feature_result.products) == len(products_traces_dictionary.keys()):
                feature_result.type = config.mandatory_str
            else:
                feature_result.type = config.optional_str
            trace2vary_results_dictionary_per_feature[feature] = feature_result

        print('4/6 - Identifying common, shared and specific products\' files for each feature')
        for (feature, feature_result) in trace2vary_results_dictionary_per_feature.items():
            files_sets = get_all_products_file_sets(products_traces_dictionary, feature, feature_result)

            # All traced files for a specific feature
            feature_result.all_files = set.union(*files_sets)
            # All traced files for a specific feature available in all products
            feature_result.common_files = set.intersection(*files_sets)
            # All traced files for a specific feature available in a single product
            feature_result.specific_files = set()
            # All traced files for a specific feature available in more than one product (and not in all products)
            feature_result.shared_files = set()

            for product in feature_result.products:
                for file in get_product_files_per_feature(products_traces_dictionary, product, feature):
                    if file not in feature_result.common_files:
                        if file in feature_result.specific_files:
                            feature_result.specific_files.remove(file)
                            feature_result.shared_files.add(file)
                        else:
                            feature_result.specific_files.add(file)

        for (key, obj) in trace2vary_results_dictionary_per_feature.items():
            print('\nFeature: ' + key)
            if obj.type == config.mandatory_str:
                print('Type: ' + obj.type)
            else:
                print('Type: ' + obj.type + ' / Products: ' + str(obj.products))
            print('All files: ' + str(obj.all_files))
            print('Common files: ' + str(obj.common_files))
            print('Shared files: ' + str(obj.shared_files))
            print('Specific files: ' + str(obj.specific_files))
