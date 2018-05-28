from bokeh.layouts import column
from bokeh.layouts import widgetbox
from bokeh.models import ColumnDataSource
from bokeh.models.widgets import DataTable, TextInput, TableColumn
from visualization.utils import get_data_frame_from_trace2vary_output


def create_table(trace2vary_output):

    text_input = TextInput(value='', title='Feature search:')

    features_data_frame = get_data_frame_from_trace2vary_output(trace2vary_output)

    data = dict(
        feature_name=features_data_frame.feature_name,
        variability=features_data_frame.variability,
        products=features_data_frame.products,
        common_files=features_data_frame.common_files,
        shared_files=features_data_frame.shared_files,
        specific_files=features_data_frame.specific_files,
        common_ratio=features_data_frame.common_ratio,
        shared_ratio=features_data_frame.shared_ratio
    )
    source = ColumnDataSource(data)

    columns = [
        # TableColumn(field="dates", title="Date", formatter=DateFormatter()),
        # TableColumn(field="downloads", title="Downloads"),
        TableColumn(field="feature_name", title="Feature"),
        TableColumn(field="variability", title="Variability type"),
        TableColumn(field="products", title="Products"),
        TableColumn(field="common_files", title="Common files count"),
        TableColumn(field="common_files_names", title="Common files"),
        TableColumn(field="shared_files", title="Shared files count"),
        TableColumn(field="shared_files_names", title="Shared files"),
        TableColumn(field="specific_files", title="Specific files count"),
        TableColumn(field="specific_files_names", title="Specific files"),
        TableColumn(field="common_ratio", title="Common files ratio"),
        TableColumn(field="shared_ratio", title="Shared files ratio")
    ]

    data_table = DataTable(source=source, columns=columns, width=1020, height=600)
    table = widgetbox(data_table)

    table_plot_column = column(text_input, table)
    return table_plot_column
