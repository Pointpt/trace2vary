setwd("/Users/tassiovale/Downloads")

# read csv file
data = read.csv("output.csv")

ggplot(data, aes(x=data$precision, y=data$features)) +
     geom_point(shape=1) +
     geom_smooth(method=lm) + theme_minimal() +
     ggtitle("Correlation - Precision x N. of features") +
     labs(x="Precision", y="N. of features") +
     scale_fill_discrete(guide=FALSE)

ggsave("correlation-precision-features.eps")