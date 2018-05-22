import config
from itertools import combinations
from commonality_and_variability.diff_analysis import calculate_diff_ratio, get_valid_files, read_files_content


class FeatureResult:
    """Description
    """
    pass


def get_all_features(traces_dictionary):
    features_set = set()
    for product in traces_dictionary.keys():
        product_features = set(traces_dictionary[product].keys())
        features_set = features_set.union(product_features)
    return features_set


def identify_products_per_feature(features_set, traces_dictionary, trace2vary_results_dictionary):
    for feature in features_set:
        feature_result = FeatureResult()
        feature_result.products = []
        for (product, traces) in traces_dictionary.items():
            if feature in traces.keys():
                feature_result.products.append(product)
        if len(feature_result.products) == len(traces_dictionary.keys()):
            feature_result.type = config.mandatory_str
        else:
            feature_result.type = config.optional_str
            trace2vary_results_dictionary[feature] = feature_result


def set_file_variability_type_per_feature(traces_dictionary, trace2vary_results_dictionary):
    for (feature, feature_result) in trace2vary_results_dictionary.items():
        files_sets = get_all_products_file_sets(traces_dictionary, feature, feature_result)

        # All traced files for a specific feature
        feature_result.all_files = set.union(*files_sets)
        # All traced files for a specific feature available in all products
        feature_result.common_files = set.intersection(*files_sets)
        # All traced files for a specific feature available in a single product
        feature_result.specific_files = set()
        # All traced files for a specific feature available in more than one product (and not in all products)
        feature_result.shared_files = set()

        for product in feature_result.products:
            for file in get_product_files_per_feature(traces_dictionary, product, feature):
                if file not in feature_result.common_files:
                    if file in feature_result.specific_files:
                        feature_result.specific_files.remove(file)
                        feature_result.shared_files.add(file)
                    else:
                        feature_result.specific_files.add(file)


def apply_diff(projects_base_path, trace2vary_results_dictionary):
    files_content_dictionary = dict()
    for (feature, feature_result) in trace2vary_results_dictionary.items():

        # Procedure for common files
        feature_result.common_files_diff_ratios = dict()
        for file in feature_result.common_files:
            products_files_names = [projects_base_path + product + '/' + file for product in feature_result.products]
            read_files_content(products_files_names, files_content_dictionary)
            pairs_of_files = list(combinations(products_files_names, 2))
            calculate_diff_ratio(
                file, pairs_of_files, files_content_dictionary, feature_result.common_files_diff_ratios
            )

        # Procedure for shared files
        feature_result.shared_files_diff_ratios = dict()
        for file in feature_result.shared_files:
            products_files_names = get_valid_files(projects_base_path, feature_result.products, file)
            read_files_content(products_files_names, files_content_dictionary)
            pairs_of_files = list(combinations(products_files_names, 2))
            calculate_diff_ratio(
                file, pairs_of_files, files_content_dictionary, feature_result.shared_files_diff_ratios
            )


def get_all_products_file_sets(products_traces_dictionary, feature, feature_result):
    files_sets = []
    for product in feature_result.products:
        files_set = get_product_files_per_feature(products_traces_dictionary, product, feature)
        files_sets.append(files_set)
    return files_sets


def get_product_files_per_feature(products_traces_dictionary, product, feature):
    files_set = set([file.rstrip('/') for file in products_traces_dictionary[product][feature]])
    return files_set
