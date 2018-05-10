#loading library
require("ggplot2")

# selecting the current directory
setwd("/Users/tassiovale/Dropbox/PhD Thesis/trace2vary/trace_recovery/results/")

# read csv file
data <- read.csv("2018-05-09_16h30m_output.csv")

chart <- ggplot(data=data, aes(x=method, y=performance, fill=method)) +
    geom_boxplot() +
    theme_minimal() +
    ggtitle("Time behavior results") +
    labs(x="IR method", y="Time behavior (in seconds)") +
    scale_fill_discrete(guide=FALSE)

ggsave("2018-05-09_16h30m_performanceavg_chart.eps")