import glob
import re


def extract_traces(project, files_extension_list):
    traces = {}
    for file_extension in files_extension_list:
        for file_name in glob.iglob(project + '/**/*' + file_extension, recursive=True):
            try:
                with open(file_name, 'r', encoding='ISO-8859-1') as source_file:
                    lines = source_file.read().splitlines()
                    for line in lines:
                        if '#' in line and ('ifdef' in line or 'ifndef' in line):
                            line = line.split('#')[1]
                            line = line.split('/*')[0]
                            line = line.split('//')[0]
                            features = re.findall('[\w]+', line)
                            file_name = file_name.replace(project, '')
                            for feature_name in features:
                                feature_name = feature_name.lower()
                                if len(feature_name) > 1:
                                    if feature_name in traces:
                                        if file_name not in traces[feature_name]:
                                            traces[feature_name] += (file_name,)
                                    else:
                                        traces[feature_name] = (file_name,)
            except IsADirectoryError:
                pass
    del traces['ifdef']
    del traces['ifndef']
    del traces['endif']
    del traces['true']
    del traces['false']
    return traces


# MAIN PROGRAM

projects = [
    '../projects/dragonflybsd/',
    '../projects/freebsd/',
    '../projects/netbsd/',
    '../projects/openbsd/',
]

print('======= IFDEF EXTRACTOR =======')

for proj in projects:
    print('\nProject: ' + proj)

    print('1/2 - Analyzing files')
    resulting_traces = extract_traces(proj, ['.c', '.h'])

    print('2/2 - Registering results')
    with open(proj + 'traceability_oracle.dat', 'a') as traceability_oracle_file, \
            open(proj + 'thesaurus.dat', 'a') as thesaurus_file:

        for feature, files_list in resulting_traces.items():
            files_list_str = str(files_list)
            if len(files_list) > 1:
                traceability_oracle_file.write(
                    feature +
                    ':' +
                    str(files_list_str).replace('(', '').replace(')', '').replace('\'', '').replace(' ', '') +
                    '\n'
                )
                #
                features_list = feature.split('_')
                processed_features_list = []
                for value in features_list:
                    if len(value) > 1:
                        processed_features_list.append(value)
                features = \
                    str(processed_features_list).replace('[', '').replace(']', '').replace('\'', '').replace(' ', '')
                thesaurus_file.write(feature + ':' + features + '\n')

print('DONE')
