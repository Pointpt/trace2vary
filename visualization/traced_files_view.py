from bokeh.layouts import row, column
from bokeh.plotting import figure
from bokeh.models import ColumnDataSource, ranges, LabelSet, NumberFormatter
import config


def create_general_data_view(trace2vary_output):

    # Mandatory x Optional features dot chart
    mandatory_features_list = []
    optional_features_list = []

    # Common, shared and specific files dot chart
    common_files_amount = 0
    shared_files_amount = 0
    specific_files_amount = 0

    #Ratio and levenshtein calculations
    common_ratio_amount = 0
    common_ratio_count = 0
    shared_ratio_amount = 0
    shared_ratio_count = 0
    common_levenshtein_amount = 0
    common_levenshtein_count = 0
    shared_levenshtein_amount = 0
    shared_levenshtein_count = 0

    for (feature_name, result) in trace2vary_output[config.result_dictionary_per_feature].items():
        if result[config.result_type] == config.optional_str:
            optional_features_list.append(feature_name)
        else:
            mandatory_features_list.append(feature_name)
        common_files_amount += len(result[config.result_common_files])
        shared_files_amount += len(result[config.result_shared_files])
        specific_files_amount += len(result[config.result_specific_files])
        if len(result[config.result_common_files]) > 1:
            common_ratios = [value for value in result[config.result_common_files_diff_ratios].values() if value != -1]
            if len(common_ratios) > 0:
                common_ratio_amount += sum(common_ratios) / len(common_ratios)
                common_ratio_count += 1
            common_lev = [value for value in result[config.result_common_files_levenshtein].values() if value != -1]
            if len(common_lev) > 0:
                common_levenshtein_amount += sum(common_lev) / len(common_lev)
                common_levenshtein_count += 1
        if len(result[config.result_shared_files]) > 1:
            shared_ratios = [value for value in result[config.result_shared_files_diff_ratios].values() if value != -1]
            if len(shared_ratios) > 0:
                shared_ratio_amount += sum(shared_ratios) / len(shared_ratios)
                shared_ratio_count += 1
            shared_lev = [value for value in result[config.result_shared_files_levenshtein].values() if value != -1]
            if len(shared_lev) > 0:
                shared_levenshtein_amount += sum(shared_lev) / len(shared_lev)
                shared_levenshtein_count += 1

    features_source = ColumnDataSource(
        dict(
            x=['Mandatory', 'Optional'],
            y=[len(mandatory_features_list), len(optional_features_list)]
        )
    )

    features_bar_chart = get_figure_from_source(features_source, 'Feature variability types', 0.2)

    files_source = ColumnDataSource(
        dict(
            x=['Common', 'Shared', 'Specific'],
            y=[common_files_amount, shared_files_amount, specific_files_amount]
        )
    )

    files_bar_chart = get_figure_from_source(files_source, 'File variability types', 0.3)

    ratio_source = ColumnDataSource(
        dict(
            x=['Common', 'Shared'],
            y=[
                round(common_ratio_amount/common_ratio_count, 2),
                round(shared_ratio_amount/shared_ratio_count, 2)
            ]
        )
    )

    ratio_bar_chart = get_figure_from_source(ratio_source, 'Common x Specific files ratio average', 0.2)

    levenshtein_source = ColumnDataSource(
        dict(
            x=['Common', 'Shared'],
            y=[
                round(common_levenshtein_amount/common_levenshtein_count, 0),
                round(shared_levenshtein_amount/shared_levenshtein_count, 0)
            ]
        )
    )

    levenshtein_bar_chart = get_figure_from_source(
        levenshtein_source, 'Common x Specific files Levenshtein distance average', 0.2
    )

    upper_row = row(features_bar_chart, files_bar_chart)
    lower_row = row(ratio_bar_chart, levenshtein_bar_chart)

    return column(upper_row, lower_row)


def get_figure_from_source(source, title, width):
    bar_chart = figure(
        title=title,
        tools='save',
        toolbar_location='above',
        x_range=source.data['x'],
        y_range=ranges.Range1d(start=0, end=max(source.data['y']) + max(source.data['y'])*0.1),
        width=600, height=300
    )

    feature_labels = LabelSet(
        x='x', y='y', text='y', level='glyph', source=source, render_mode='canvas', x_offset=-25
    )
    bar_chart.vbar(source=source, x='x', top='y', bottom=0, width=width)
    bar_chart.add_layout(feature_labels)

    return bar_chart
