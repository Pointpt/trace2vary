#loading library
require("ggplot2")

# selecting the current directory
setwd("/Users/tassiovale/Dropbox/PhD Thesis/trace2vary/trace_recovery/results/")

# read csv file
data <- read.csv("results_output.csv")

chart <- ggplot(data=data, aes(x=recall, y=precision, group=method, colour=method)) +
    geom_line() +
    geom_point(aes(shape=method)) +
    ggtitle("Precision x recall") +
    labs(x="Recall", y="Precision") +
    scale_fill_discrete(name="IR method")

ggsave("results_precisionrecall_chart.eps")
