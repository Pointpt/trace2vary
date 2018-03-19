# read csv file
data = read.csv("2017-05-03_13h53m_output.csv")

data_lsi = data[data$method=='Latent semantic indexing',]
data_classic_vector = data[data$method=='Classic vector model',]
data_neural_network = data[data$method=='Neural networks',]
data_extended_boolean = data[data$method=='Extended boolean',]
data_bm25 = data[data$method=='BM25',]

cat("\n\n\n")
print("Student's t test - F-MEASURE")

print("Latent semantic indexing < Classic vector model")
result = t.test(data_lsi$fmeasure,data_classic_vector$fmeasure, paired=TRUE, alt="less")
print(result)

print("Latent semantic indexing < Neural networks")
result = t.test(data_lsi$fmeasure,data_neural_network$fmeasure, paired=TRUE, alt="less")
print(result)

print("Latent semantic indexing < Extended boolean")
result = t.test(data_lsi$fmeasure,data_extended_boolean$fmeasure, paired=TRUE, alt="less")
print(result)

print("Latent semantic indexing < BM25")
result = t.test(data_lsi$fmeasure,data_bm25$fmeasure, paired=TRUE, alt="less")
print(result)

cat("\n\n\n")
print("Student's t test - PRECISION")

print("Latent semantic indexing < Classic vector model")
result = t.test(data_lsi$precision,data_classic_vector$precision, paired=TRUE, alt="less")
print(result)

print("Latent semantic indexing < Neural networks")
result = t.test(data_lsi$precision,data_neural_network$precision, paired=TRUE, alt="less")
print(result)

print("Latent semantic indexing < Extended boolean")
result = t.test(data_lsi$precision,data_extended_boolean$precision, paired=TRUE, alt="less")
print(result)

print("Latent semantic indexing < BM25")
result = t.test(data_lsi$precision,data_bm25$precision, paired=TRUE, alt="less")
print(result)

cat("\n\n\n")
print("Student's t test - RECALL")

print("Latent semantic indexing < Classic vector model")
result = t.test(data_lsi$recall,data_classic_vector$recall, paired=TRUE, alt="less")
print(result)

print("Latent semantic indexing < Neural networks")
result = t.test(data_lsi$recall,data_neural_network$recall, paired=TRUE, alt="less")
print(result)

print("Latent semantic indexing < Extended boolean")
result = t.test(data_lsi$recall,data_extended_boolean$recall, paired=TRUE, alt="less")
print(result)

print("Latent semantic indexing < BM25")
result = t.test(data_lsi$recall,data_bm25$recall, paired=TRUE, alt="less")
print(result)