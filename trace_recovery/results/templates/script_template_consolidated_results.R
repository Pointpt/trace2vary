#loading library
require("ggplot2")

setwd("/Users/tassiovale/Downloads")

# read csv file
data = read.csv("data-consolidated.csv")

ggplot(data=data, aes(x=sample, y=fmeasure, fill=Method)) +
    geom_boxplot() +
    theme(legend.position="bottom", text=element_text(size=20, colour="black"),
    legend.key.width=unit(3,"line"), axis.ticks=element_line(colour="black")) +
    scale_fill_discrete("") +
    ggtitle("") +
    labs(x="", y="")

ggsave("box.eps")
