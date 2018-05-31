from collections import OrderedDict
from math import log, sqrt
import numpy as np
from bokeh.plotting import figure
import sys
import warnings
import config
from visualization.utils import get_data_frame_from_trace2vary_output


def create_burtin_chart(trace2vary_output):

    if not sys.warnoptions:
        warnings.simplefilter('ignore')

    features_data_frame = get_data_frame_from_trace2vary_output(trace2vary_output)

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

    width = 600
    height = 600
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

    plot = figure(
        plot_width=width, plot_height=height, title='Features overview',
        x_axis_type=None, y_axis_type=None,
        x_range=(-420, 420), y_range=(-420, 420),
        min_border=0, outline_line_color='black',
        background_fill_color='#f0e1d2',
        toolbar_location='right',
        tools='pan,zoom_in,zoom_out,wheel_zoom,box_zoom,save,reset',
    )

    plot.xgrid.grid_line_color = None
    plot.ygrid.grid_line_color = None

    # annular wedges
    angles = np.pi/2 - big_angle/2 - features_data_frame.index.to_series()*big_angle
    colors = [variability_color[variability] for variability in features_data_frame.variability]
    plot.annular_wedge(
        0, 0, inner_radius, outer_radius, -big_angle+angles, angles, color=colors,
    )

    # small wedges
    plot.annular_wedge(
        0, 0, inner_radius, rad(features_data_frame.common_files.astype(int)),
        -big_angle+angles+5*small_angle, -big_angle+angles+6*small_angle,
        color=file_type_color['Common files']
    )
    plot.annular_wedge(
        0, 0, inner_radius, rad(features_data_frame.shared_files.astype(int)),
        -big_angle+angles+3*small_angle, -big_angle+angles+4*small_angle,
        color=file_type_color['Shared files']
    )
    plot.annular_wedge(
        0, 0, inner_radius, rad(features_data_frame.specific_files.astype(int)),
        -big_angle+angles+1*small_angle, -big_angle+angles+2*small_angle,
        color=file_type_color['Specific files']
    )

    # circular axes and labels
    labels = np.power(10.0, np.arange(-3, 4))
    radii = a * np.sqrt(np.log(labels * 1E4)) + b
    plot.circle(0, 0, radius=radii, fill_color=None, line_color='white')
    plot.text(
        0, radii[:-1], [str(r) for r in labels],
        text_font_size='8pt', text_align='center', text_baseline='middle'
    )

    # radial axes
    plot.annular_wedge(
        0, 0, inner_radius-10, outer_radius+10,
        -big_angle+angles, -big_angle+angles, color='black'
    )

    # feature_name labels
    xr = radii[0]*np.cos(np.array(-big_angle/2 + angles))
    yr = radii[0]*np.sin(np.array(-big_angle/2 + angles))
    label_angle = np.array(-big_angle/2+angles)
    label_angle[label_angle < -np.pi/2] += np.pi  # easier to read labels on the left side
    plot.text(
        xr, yr, features_data_frame.feature_name, angle=label_angle,
        text_font_size='9pt', text_align='center', text_baseline='middle'
    )

    # OK, these hand drawn legends are pretty clunky, will be improved in future release
    plot.circle([-40, -40], [-370, -390], color=list(variability_color.values()), radius=5)
    plot.text(
        [-30, -30], [-370, -390], text=[gr.title() + ' feature' for gr in variability_color.keys()],
        text_font_size='9pt', text_align='left', text_baseline='middle'
    )

    plot.rect(
        [-40, -40, -40], [18, 0, -18], width=30, height=13,
        color=list(file_type_color.values())
    )
    plot.text(
        [-15, -15, -15], [18, 0, -18], text=list(file_type_color),
        text_font_size='9pt', text_align='left', text_baseline='middle'
    )

    return plot
