from learning.trace_recovery.svm import run_svm
from learning.trace_recovery.neural_network import run_neural_network
from learning.trace_recovery.sgd import run_sgd
from learning.trace_recovery.kernel_approximation import run_kernel_approximation
# from learning.trace_recovery.auto_learning import run_auto_learning

config_file = '../projects/training_set.dat'

# Support Vector Machine method
run_svm(config_file)

# Neural Network method
run_neural_network(config_file)

# Stochastic Gradient Descent method
run_sgd(config_file)

# Kernel Approximation method
run_kernel_approximation(config_file)

# Auto Learning method
# run_auto_learning()
