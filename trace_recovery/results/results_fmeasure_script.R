#loading library
require("ggplot2")

# selecting the current directory
setwd("/Users/tassiovale/Dropbox/PhD Thesis/trace2vary/trace_recovery/results/")

# read csv file
data <- read.csv("results_output.csv")

ggplot(data=data, aes(x=method, y=fmeasure, fill=method)) +
    geom_boxplot() +
    theme_minimal() +
    ggtitle("F-measure per method") +
    labs(x="IR method", y="F-measure") +
    scale_fill_discrete(guide=FALSE)

ggsave("results_fmeasure_chart.eps")
