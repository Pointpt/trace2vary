from bokeh.layouts import row
from bokeh.plotting import figure, show, output_file
from bokeh.models import ColumnDataSource, ranges, LabelSet
import config


def create_general_data_view(trace2vary_output):

    # Mandatory x Optional features dot chart
    mandatory_features_list = []
    optional_features_list = []
    for (feature_name, result) in trace2vary_output[config.result_dictionary_per_feature].items():
        if result[config.result_type] == config.optional_str:
            optional_features_list.append(feature_name)
        else:
            mandatory_features_list.append(feature_name)

    features_source = ColumnDataSource(
        dict(
            x=['Mandatory', 'Optional'],
            y=[len(mandatory_features_list), len(optional_features_list)]
        )
    )

    features_bar_chart = get_figure_from_source(features_source, 'Feature variability types', 0.2)

    # Common, shared and specific files dot chart
    traced_files = 0
    common_files_amount = 0
    shared_files_amount = 0
    specific_files_amount = 0
    for result in trace2vary_output[config.result_dictionary_per_feature].values():
        traced_files += len(result[config.result_all_files])
        common_files_amount += len(result[config.result_common_files])
        shared_files_amount += len(result[config.result_shared_files])
        specific_files_amount += len(result[config.result_specific_files])

    files_source = ColumnDataSource(
        dict(
            x=['All types', 'Common', 'Shared', 'Specific'],
            y=[traced_files, common_files_amount, shared_files_amount, specific_files_amount]
        )
    )

    files_bar_chart = get_figure_from_source(files_source, 'File variability types', 0.4)

    output_file('output/trace2vary_bar_chart.html', title='trace2vary - General data')

    show(row(features_bar_chart, files_bar_chart, sizing_mode='scale_width'))


def get_figure_from_source(source, title, width):
    bar_chart = figure(
        title=title,
        tools='save',
        toolbar_location='above',
        x_range=source.data['x'],
        y_range=ranges.Range1d(start=0, end=max(source.data['y']) + 100)
    )

    feature_labels = LabelSet(
        x='x', y='y', text='y', level='glyph', source=source, render_mode='canvas', x_offset=-25
    )
    bar_chart.vbar(source=source, x='x', top='y', bottom=0, width=width)
    bar_chart.add_layout(feature_labels)

    return bar_chart
