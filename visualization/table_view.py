from bokeh.layouts import column, row, widgetbox
from bokeh.models import ColumnDataSource, CustomJS, NumberFormatter
from bokeh.models.widgets import DataTable, TextInput, TableColumn, PreText
from visualization.utils import get_data_frame_from_trace2vary_output
# Source: https://gist.github.com/dennisobrien/450d7da20daaba6d39d0


def create_table(trace2vary_output):

    features_data_frame = get_data_frame_from_trace2vary_output(trace2vary_output)

    source = get_column_data_source_from_data_frame(features_data_frame)
    original_source = get_column_data_source_from_data_frame(features_data_frame)

    legend_1 = column(
        PreText(
            text="""Not applicable (N/A): -1
CA - Common files amount
CR - Common files ratio average
CL - Common files Levenshtein distance average""",
            width=400
        )
    )
    legend_2 = column(
        PreText(
            text="""ShA - Shared files amount
ShR - Shared files ratio average
ShL - Shared files Levenshtein distance average
SpA - Specific files amount""",
            width=400
        )
    )
    legend = row(legend_1, legend_2)

    number_formatter_decimal = NumberFormatter(format='0.00')
    number_formatter_int = NumberFormatter(format='0')
    columns = [
        TableColumn(field='feature_name', title='Feature', width=200),
        TableColumn(field='variability', title='Variability', width=100),
        TableColumn(field='products', title='Products', width=200),
        TableColumn(field='common_files_names', title='Common files'),
        TableColumn(field='common_files', title='CA', width=25),
        TableColumn(field='common_ratio', title='CR', width=55, formatter=number_formatter_decimal),
        TableColumn(field='common_levenshtein', title='CL', width=55, formatter=number_formatter_int),
        TableColumn(field='shared_files_names', title='Shared files'),
        TableColumn(field='shared_files', title='ShA', width=25),
        TableColumn(field='shared_ratio', title='ShR', width=55, formatter=number_formatter_decimal),
        TableColumn(field='shared_levenshtein', title='ShL', width=55, formatter=number_formatter_int),
        TableColumn(field='specific_files_names', title='Specific files'),
        TableColumn(field='specific_files', title='SpA', width=25)
    ]

    data_table = DataTable(
        source=source,
        columns=columns,
        width=1250,
        height=520,
        editable=True,
        fit_columns=True,
        selectable=True
    )
    table = widgetbox(data_table)

    text_input = TextInput(title='Type a feature name and press Enter:')
    callback = CustomJS(
        args=dict(
            source=source,
            original_source=original_source,
            target_obj=data_table
        ),
        code="""
            var data = source.data;
            var original_data = original_source.data;
            var text = cb_obj.value
            
            for (var key in original_data) {
                data[key] = [];
            }
            
            for (var i = 0; i < original_data["feature_name"].length; ++i) {
                if (original_data["feature_name"][i].includes(text)) {
                    for (var key in original_data) {
                        data[key].push(original_data[key][i]);
                    }
                }
                
            }
            console.log(text)
            target_obj.change.emit();
            source.change.emit();
        """
    )
    text_input.js_on_change('value', callback)

    table_plot_column = column(row(text_input, legend), table)
    return table_plot_column


def get_column_data_source_from_data_frame(features_data_frame):
    return ColumnDataSource(
        data=dict(
            feature_name=features_data_frame.feature_name,
            variability=features_data_frame.variability,
            products=features_data_frame.products,
            common_files_names=features_data_frame.common_files_names,
            common_files=features_data_frame.common_files,
            common_ratio=features_data_frame.common_ratio,
            common_levenshtein=features_data_frame.common_levenshtein,
            shared_files_names=features_data_frame.shared_files_names,
            shared_files=features_data_frame.shared_files,
            shared_ratio=features_data_frame.shared_ratio,
            shared_levenshtein=features_data_frame.shared_levenshtein,
            specific_files=features_data_frame.specific_files,
            specific_files_names=features_data_frame.specific_files_names
        )
    )
