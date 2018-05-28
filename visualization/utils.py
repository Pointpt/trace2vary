import pandas as pd
import config


def get_data_frame_from_trace2vary_output(trace2vary_output):
    columns = [
        'feature_name', 'variability', 'products',
        'common_files', 'common_files_names', 'common_ratio',
        'shared_files', 'shared_files_names', 'shared_ratio',
        'specific_files', 'specific_files_names'
    ]
    features_data_frame = pd.DataFrame(columns=columns)

    for (feature_name, result) in trace2vary_output[config.result_dictionary_per_feature].items():
        variability = result[config.result_type]
        products = result[config.result_products]
        common_files_names = result[config.result_common_files]
        common_files = len(result[config.result_common_files])
        shared_files_names = result[config.result_shared_files]
        shared_files = len(result[config.result_shared_files])
        specific_files_names = result[config.result_specific_files]
        specific_files = len(result[config.result_specific_files])
        common_ratio = 0
        shared_ratio = 0
        features_data_frame.loc[-1] = [
            feature_name, variability, products,
            common_files, common_files_names, common_ratio,
            shared_files, shared_files_names, shared_ratio,
            specific_files, specific_files_names
        ]
        features_data_frame.index = features_data_frame.index + 1

    features_data_frame = features_data_frame.sort_index()
    return features_data_frame
