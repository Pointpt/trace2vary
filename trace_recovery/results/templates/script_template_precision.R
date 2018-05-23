#loading library
require("ggplot2")

# selecting the current directory
setwd("<directory>")

# read csv file
data <- read.csv("<output_file_name>")

chart <- ggplot(data=data, aes(x=method, y=precision, fill=method)) +
    geom_boxplot() +
    theme_minimal() +
    ggtitle("Precision per method") +
    labs(x="IR method", y="Precision") +
    scale_fill_discrete(guide=FALSE)

ggsave("<pdf_image_file_name>.eps")