# selecting the current directory
setwd("/Users/tassiovale/Dropbox/PhD Thesis/trace2vary/trace_recovery/results/")

# read csv file
data = read.csv("results_output.csv")

data_classic_vector = data[data$method=='CV',]
data_neural_network = data[data$method=='NN',]
data_extended_boolean = data[data$method=='EB',]
data_bm25 = data[data$method=='BM25',]
data_svm = data[data$method=='t2v-SGD',]
data_auto = data[data$method=='t2v-AutoML',]

cat("\n\n\n")
print("Student's t test - F-MEASURE")

print("SVM > Classic vector model")
result = t.test(data_svm$fmeasure,data_classic_vector$fmeasure, paired=TRUE, alt="greater")
print(result)

print("SVM > Neural networks")
result = t.test(data_svm$fmeasure,data_neural_network$fmeasure, paired=TRUE, alt="greater")
print(result)

print("SVM > Extended boolean")
result = t.test(data_svm$fmeasure,data_extended_boolean$fmeasure, paired=TRUE, alt="greater")
print(result)

print("SVM > BM25")
result = t.test(data_svm$fmeasure,data_bm25$fmeasure, paired=TRUE, alt="greater")
print(result)

print("AutoML > Classic vector model")
result = t.test(data_auto$fmeasure,data_classic_vector$fmeasure, paired=TRUE, alt="greater")
print(result)

print("AutoML > Neural networks")
result = t.test(data_auto$fmeasure,data_neural_network$fmeasure, paired=TRUE, alt="greater")
print(result)

print("AutoML > Extended boolean")
result = t.test(data_auto$fmeasure,data_extended_boolean$fmeasure, paired=TRUE, alt="greater")
print(result)

print("AutoML > BM25")
result = t.test(data_auto$fmeasure,data_bm25$fmeasure, paired=TRUE, alt="greater")
print(result)

cat("\n\n\n")
print("Student's t test - PRECISION")

print("SVM > Classic vector model")
result = t.test(data_svm$precision,data_classic_vector$precision, paired=TRUE, alt="greater")
print(result)

print("SVM > Neural networks")
result = t.test(data_svm$precision,data_neural_network$precision, paired=TRUE, alt="greater")
print(result)

print("SVM > Extended boolean")
result = t.test(data_svm$precision,data_extended_boolean$precision, paired=TRUE, alt="greater")
print(result)

print("SVM > BM25")
result = t.test(data_svm$precision,data_bm25$precision, paired=TRUE, alt="greater")
print(result)

print("AutoML > Classic vector model")
result = t.test(data_auto$precision,data_classic_vector$precision, paired=TRUE, alt="greater")
print(result)

print("AutoML > Neural networks")
result = t.test(data_auto$precision,data_neural_network$precision, paired=TRUE, alt="greater")
print(result)

print("AutoML > Extended boolean")
result = t.test(data_auto$precision,data_extended_boolean$precision, paired=TRUE, alt="greater")
print(result)

print("AutoML > BM25")
result = t.test(data_auto$precision,data_bm25$precision, paired=TRUE, alt="greater")
print(result)

cat("\n\n\n")
print("Student's t test - RECALL")

print("SVM > Classic vector model")
result = t.test(data_svm$recall,data_classic_vector$recall, paired=TRUE, alt="greater")
print(result)

print("SVM > Neural networks")
result = t.test(data_svm$recall,data_neural_network$recall, paired=TRUE, alt="greater")
print(result)

print("SVM > Extended boolean")
result = t.test(data_svm$recall,data_extended_boolean$recall, paired=TRUE, alt="greater")
print(result)

print("SVM > BM25")
result = t.test(data_svm$recall,data_bm25$recall, paired=TRUE, alt="greater")
print(result)

print("AutoML > Classic vector model")
result = t.test(data_auto$recall,data_classic_vector$recall, paired=TRUE, alt="greater")
print(result)

print("AutoML > Neural networks")
result = t.test(data_auto$recall,data_neural_network$recall, paired=TRUE, alt="greater")
print(result)

print("AutoML > Extended boolean")
result = t.test(data_auto$recall,data_extended_boolean$recall, paired=TRUE, alt="greater")
print(result)

print("AutoML > BM25")
result = t.test(data_auto$recall,data_bm25$recall, paired=TRUE, alt="greater")
print(result)
