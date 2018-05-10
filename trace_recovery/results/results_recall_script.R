#loading library
require("ggplot2")

# selecting the current directory
setwd("/Users/tassiovale/Dropbox/PhD Thesis/trace2vary/trace_recovery/results/")

# read csv file
data <- read.csv("results_output.csv")

chart <- ggplot(data=data, aes(x=method, y=recall, fill=method)) +
    geom_boxplot() +
    theme_minimal() +
    ggtitle("Recall per method") +
    labs(x="IR method", y="Recall") +
    scale_fill_discrete(guide=FALSE)

ggsave("results_recall_chart.eps")
