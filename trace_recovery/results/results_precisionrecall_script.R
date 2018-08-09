#loading library
require("ggplot2")

# selecting the current directory
setwd("/Users/tassiovale/Dropbox/PhD Thesis/trace2vary/trace_recovery/results/")

# read csv file
data <- read.csv("results_output.csv")

chart <- ggplot(data=data, aes(x=recall, y=precision, group=method, colour=method)) +
    geom_line() +
scale_fill_grey(start = 0, end = .9) +
guides(fill=FALSE) +
ggtitle("") +
labs(x="", y="") +
theme_grey(base_size = 16) +
xlab("IR method") +
ylab("Value")

ggsave("results_precisionrecall_chart.eps")
