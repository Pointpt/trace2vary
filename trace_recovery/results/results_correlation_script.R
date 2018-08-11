# selecting the current directory
setwd("/Users/tassiovale/Dropbox/PhD Thesis/trace2vary/trace_recovery/results/")

# read csv file
all_data = read.csv("results_output.csv")
data_svm_temp = all_data[all_data$method=='t2v-SGD',]
data_auto_temp = all_data[all_data$method=='t2v-AutoML',]

data_svm = data_svm_temp[ , !names(data_svm_temp) %in% c("project","language","variability_impl_technology","method")]

data_auto = data_auto_temp[ , !names(data_auto_temp) %in% c("project","language","variability_impl_technology","method")]

cat("\n\n\n")
print("Pearson correlation - SVM")
result = cor(data_svm, method="pearson")
print(result)

cat("\n\n\n")
print("Pearson correlation - AutoML")
result = cor(data_auto, method="pearson")
print(result)


