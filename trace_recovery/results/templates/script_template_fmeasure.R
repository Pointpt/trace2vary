#loading library
require("ggplot2")

# selecting the current directory
setwd("<directory>")

# read csv file
data <- read.csv("<output_file_name>")

ggplot(data=data, aes(x=method, y=fmeasure, fill=method)) +
    geom_boxplot() +
    theme_minimal() +
    ggtitle("F-measure per method") +
    labs(x="IR method", y="F-measure") +
    scale_fill_discrete(guide=FALSE)

ggsave("<pdf_image_file_name>.eps")