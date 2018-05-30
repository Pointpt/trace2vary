from bokeh.layouts import column, widgetbox
from bokeh.models import ColumnDataSource, CustomJS
from bokeh.models.widgets import DataTable, TextInput, TableColumn
from visualization.utils import get_data_frame_from_trace2vary_output
# Source: https://gist.github.com/dennisobrien/450d7da20daaba6d39d0


def create_table(trace2vary_output):

    features_data_frame = get_data_frame_from_trace2vary_output(trace2vary_output)

    source = get_column_data_source_from_data_frame(features_data_frame)
    original_source = get_column_data_source_from_data_frame(features_data_frame)

    columns = [
        TableColumn(field='feature_name', title='Feature', sortable=True),
        TableColumn(field='variability', title='Variability', width=100),
        TableColumn(field='products', title='Products'),
        TableColumn(field='common_files', title='CmF', width=25),
        TableColumn(field='common_files_names', title='Common files'),
        TableColumn(field='shared_files', title='ShF', width=25),
        TableColumn(field='shared_files_names', title='Shared files'),
        TableColumn(field='specific_files', title='SpF', width=25),
        TableColumn(field='specific_files_names', title='Specific files'),
        TableColumn(field='common_ratio', title='CFR', width=25),
        TableColumn(field='shared_ratio', title='ShFR', width=25)
    ]

    data_table = DataTable(source=source, columns=columns, width=1020, height=600)
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

    table_plot_column = column(text_input, table)
    return table_plot_column


def get_column_data_source_from_data_frame(features_data_frame):
    return ColumnDataSource(
        data=dict(
            feature_name=features_data_frame.feature_name,
            variability=features_data_frame.variability,
            products=features_data_frame.products,
            common_files=features_data_frame.common_files,
            common_files_names=features_data_frame.common_files_names,
            shared_files=features_data_frame.shared_files,
            shared_files_names=features_data_frame.shared_files_names,
            specific_files=features_data_frame.specific_files,
            specific_files_names=features_data_frame.specific_files_names,
            common_ratio=features_data_frame.common_ratio,
            shared_ratio=features_data_frame.shared_ratio
        )
    )