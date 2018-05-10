#loading library
require("ggplot2")

# selecting the current directory
setwd("/Users/tassiovale/Dropbox/PhD Thesis/trace2vary/trace_recovery/results/")

# read csv file
data <- read.csv("2018-05-02_15h43m_output.csv")

ggplot(data=data, aes(x=method, y=fmeasure, fill=method)) +
    geom_boxplot() +
    theme_minimal() +
    ggtitle("F-measure per method") +
    labs(x="IR method", y="F-measure") +
    scale_fill_discrete(guide=FALSE)

ggsave("2018-05-02_15h43m_fmeasure_chart.eps")