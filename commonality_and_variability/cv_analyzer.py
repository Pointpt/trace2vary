import config
import json
# https://docs.python.org/2.7/library/difflib.html
# feature 1 - diff ratio quick_ratio()
# edit distance described by Levenshtein


class FeatureResult:
    """Description
    """
    pass


def compare_products():

    print('===== COMMONALITY AND VARIABILITY ANALYSIS =====')

    products_traces_dictionary = dict()
    features_results_dictionary = dict()
    with open(config.test_set_file, 'r') as products_file:

        print('1/3 - Reading products\' traces')

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

        print('2/3 - Gathering the full set of features')
        features_set = set()
        for product in products_traces_dictionary.keys():
            product_features = set(products_traces_dictionary[product].keys())
            features_set = features_set.union(product_features)

        for feature in features_set:
            feature_result = FeatureResult()
            feature_result.products = []
            for product in products_traces_dictionary.keys():
                if feature in products_traces_dictionary[product].keys():
                    feature_result.products.append(product)
            features_results_dictionary[feature] = feature_result

        # for (key, obj) in features_results_dictionary.items():
        #     print(str(obj.products))
