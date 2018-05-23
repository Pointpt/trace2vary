#loading library - it requires the installation of the effsize package
require("effsize")

# selecting the current directory
setwd("/Users/tassiovale/Downloads/spltrac")

# read csv file
dataspl <- read.csv("data-spl-withLSI.csv")
dataprep <- read.csv("data_preprocessor.csv")

dataspl_cv = dataspl[dataspl$method=='Classic vector model',]
dataprep_cv = dataprep[dataprep$method=='Classic vector model',]

dataspl_eb = dataspl[dataspl$method=='Extended boolean',]
dataprep_eb = dataprep[dataprep$method=='Extended boolean',]

dataspl_nn = dataspl[dataspl$method=='Neural networks',]
dataprep_nn = dataprep[dataprep$method=='Neural networks',]

dataspl_bm25 = dataspl[dataspl$method=='BM25',]
dataprep_bm25 = dataprep[dataprep$method=='BM25',]

cat("======= PRECISION =======")

cat("\n\nGeneral")

result = cohen.d(dataspl$precision,dataprep$precision,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\nClassic vector")

result = cohen.d(dataspl_cv$precision,dataprep_cv$precision,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\nExtended boolean")

result = cohen.d(dataspl_eb$precision,dataprep_eb$precision,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\nNeural networks")

result = cohen.d(dataspl_nn$precision,dataprep_nn$precision,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\nBM25")

result = cohen.d(dataspl_bm25$precision,dataprep_bm25$precision,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\n\n\n======= RECALL =======")

cat("\n\nGeneral")

result = cohen.d(dataspl$recall,dataprep$recall,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\nClassic vector")

result = cohen.d(dataspl_cv$recall,dataprep_cv$recall,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\nExtended boolean")

result = cohen.d(dataspl_eb$recall,dataprep_eb$recall,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\nNeural networks")

result = cohen.d(dataspl_nn$recall,dataprep_nn$recall,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\nBM25")

result = cohen.d(dataspl_bm25$recall,dataprep_bm25$recall,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\n\n\n======= F-MEASURE =======")

cat("\n\nGeneral")

result = cohen.d(dataspl$fmeasure,dataprep$fmeasure,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\nClassic vector")

result = cohen.d(dataspl_cv$fmeasure,dataprep_cv$fmeasure,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\nExtended boolean")

result = cohen.d(dataspl_eb$fmeasure,dataprep_eb$fmeasure,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\nNeural networks")

result = cohen.d(dataspl_nn$fmeasure,dataprep_nn$fmeasure,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\nBM25")

result = cohen.d(dataspl_bm25$fmeasure,dataprep_bm25$fmeasure,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\n\n\n======= TIME BEHAVIOR =======")

cat("\n\nGeneral")

result = cohen.d(dataspl$performance,dataprep$performance,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\nClassic vector")

result = cohen.d(dataspl_cv$performance,dataprep_cv$performance,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\nExtended boolean")

result = cohen.d(dataspl_eb$performance,dataprep_eb$performance,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\nNeural networks")

result = cohen.d(dataspl_nn$performance,dataprep_nn$performance,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))

cat("\n\nBM25")

result = cohen.d(dataspl_bm25$performance,dataprep_bm25$performance,paired=FALSE,hedges.correction=TRUE)
print(result)
print(summary(result))
