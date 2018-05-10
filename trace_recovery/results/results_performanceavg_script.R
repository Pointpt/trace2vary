#loading library
require("ggplot2")

# selecting the current directory
setwd("/Users/tassiovale/Dropbox/PhD Thesis/trace2vary/trace_recovery/results/")

# read csv file
data <- read.csv("results_output.csv")

chart <- ggplot(data=data, aes(x=method, y=performance, fill=method)) +
    geom_boxplot() +
    theme_minimal() +
    ggtitle("Time behavior results") +
    labs(x="IR method", y="Time behavior (in seconds)") +
    scale_fill_discrete(guide=FALSE)

ggsave("results_performanceavg_chart.eps")
