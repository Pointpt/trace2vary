# complete_set_file = 'projects/_preprocessor_complete_set.dat'
# training_set_file = 'projects/_preprocessor_training_set.dat'
# test_set_file = 'projects/_preprocessor_training_set.dat'

complete_set_file = 'projects/_bsd_test_set.dat'
training_set_file = 'projects/_preprocessor_training_set.dat'
test_set_file = 'projects/_bsd_test_set.dat'

arg_pre_process_projects = '-p'
arg_trace_recovery = '-tr'
arg_fit_machine_learning_model = '-fit'
arg_cv_analysis = '-cv'
arg_only_sgd = '-only-sgd'

# sgd_file = 'trace_recovery/preprocessor_sgd.pkl'
sgd_file = 'trace_recovery/bsd_sgd.pkl'
sgd = 'sgd'

# svm_file = 'trace_recovery/preprocessor_svm.pkl'
svm_file = 'trace_recovery/bsd_svm.pkl'
svm = 'svm'

traces_file = 'sgd_traces.json'
# traces_file = 'svm_traces.json'

mandatory_str = 'mandatory'
optional_str = 'optional'
