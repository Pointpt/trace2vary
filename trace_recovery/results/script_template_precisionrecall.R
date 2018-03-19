#loading library
require("ggplot2")

# selecting the current directory
setwd("<directory>")

# read csv file
data <- read.csv("<output_file_name>")

chart <- ggplot(data=data, aes(x=recall, y=precision, group=method, colour=method)) +
    geom_line() +
    geom_point(aes(shape=method)) +
    ggtitle("Precision x recall") +
    labs(x="Recall", y="Precision") +
    scale_fill_discrete(name="IR method")

ggsave("<pdf_image_file_name>.eps")