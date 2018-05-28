from collections import OrderedDict
from math import log, sqrt
import numpy as np
import pandas as pd
from bokeh.plotting import figure, show, output_file
import config


def create_burtin_chart(trace2vary_output):

    columns = [
        'feature_name', 'variability', 'common_files', 'shared_files', 'specific_files', 'common_ratio', 'shared_ratio'
    ]
    features_data_frame = pd.DataFrame(columns=columns)

    for (feature_name, result) in trace2vary_output[config.result_dictionary_per_feature].items():
        variability = result[config.result_type]
        common_files = len(result[config.result_common_files])
        shared_files = len(result[config.result_shared_files])
        specific_files = len(result[config.result_specific_files])
        common_ratio = 0
        shared_ratio = 0
        features_data_frame.loc[-1] = [feature_name, variability, common_files, shared_files, specific_files, common_ratio, shared_ratio]
        features_data_frame.index = features_data_frame.index + 1

    features_data_frame = features_data_frame.sort_index()

    file_type_color = OrderedDict(
        [
            ('Common files', 'black'),
            ('Shared files', '#0d3362'),
            ('Specific files', '#c64737')
        ]
    )

    variability_color = {
        config.mandatory_str: '#aeaeb8',
        config.optional_str: '#e69584'
    }

    width = 800
    height = 800
    inner_radius = 90
    outer_radius = 300 - 10

    minr = sqrt(log(.001 * 1E4))
    maxr = sqrt(log(1000 * 1E4))
    a = (outer_radius - inner_radius) / (minr - maxr)
    b = inner_radius - a * maxr

    def rad(mic):
        return a * np.sqrt(np.log(mic * 1E4)) + b

    big_angle = 2.0 * np.pi / (len(features_data_frame) + 1)
    small_angle = big_angle / 7

    p = figure(
        plot_width=width, plot_height=height, title='Features overview',
        x_axis_type=None, y_axis_type=None,
        x_range=(-420, 420), y_range=(-420, 420),
        min_border=0, outline_line_color='black',
        background_fill_color='#f0e1d2',
        toolbar_location='above',
        tools='pan,wheel_zoom,save,reset'
    )

    p.xgrid.grid_line_color = None
    p.ygrid.grid_line_color = None

    # annular wedges
    angles = np.pi/2 - big_angle/2 - features_data_frame.index.to_series()*big_angle
    colors = [variability_color[variability] for variability in features_data_frame.variability]
    p.annular_wedge(
        0, 0, inner_radius, outer_radius, -big_angle+angles, angles, color=colors,
    )

    # small wedges
    p.annular_wedge(0, 0, inner_radius, rad(features_data_frame.common_files.astype(int)),
                    -big_angle+angles+5*small_angle, -big_angle+angles+6*small_angle,
                    color=file_type_color['Common files'])
    p.annular_wedge(0, 0, inner_radius, rad(features_data_frame.shared_files.astype(int)),
                    -big_angle+angles+3*small_angle, -big_angle+angles+4*small_angle,
                    color=file_type_color['Shared files'])
    p.annular_wedge(0, 0, inner_radius, rad(features_data_frame.specific_files.astype(int)),
                    -big_angle+angles+1*small_angle, -big_angle+angles+2*small_angle,
                    color=file_type_color['Specific files'])

    # circular axes and labels
    labels = np.power(10.0, np.arange(-3, 4))
    print(labels)
    radii = a * np.sqrt(np.log(labels * 1E4)) + b
    p.circle(0, 0, radius=radii, fill_color=None, line_color='white')
    p.text(0, radii[:-1], [str(r) for r in labels[:-1]],
           text_font_size='8pt', text_align='center', text_baseline='middle')

    # radial axes
    p.annular_wedge(0, 0, inner_radius-10, outer_radius+10,
                    -big_angle+angles, -big_angle+angles, color='black')

    # bacteria labels
    xr = radii[0]*np.cos(np.array(-big_angle/2 + angles))
    yr = radii[0]*np.sin(np.array(-big_angle/2 + angles))
    label_angle = np.array(-big_angle/2+angles)
    label_angle[label_angle < -np.pi/2] += np.pi  # easier to read labels on the left side
    p.text(xr, yr, features_data_frame.feature_name, angle=label_angle,
           text_font_size='9pt', text_align='center', text_baseline='middle')

    # OK, these hand drawn legends are pretty clunky, will be improved in future release
    p.circle([-40, -40], [-370, -390], color=list(variability_color.values()), radius=5)
    p.text([-30, -30], [-370, -390], text=[gr.title() + ' feature' for gr in variability_color.keys()],
           text_font_size='9pt', text_align='left', text_baseline='middle')

    p.rect([-40, -40, -40], [18, 0, -18], width=30, height=13,
           color=list(file_type_color.values()))
    p.text([-15, -15, -15], [18, 0, -18], text=list(file_type_color),
           text_font_size='9pt', text_align='left', text_baseline='middle')

    output_file('output/trace2vary_details_chart.html', title='Feature details')

    show(p)
