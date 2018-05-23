#loading library
require("ggplot2")

# selecting the current directory
setwd("<directory>")

# read csv file
data <- read.csv("<output_file_name>")

chart <- ggplot(data=data, aes(x=method, y=recall, fill=method)) +
    geom_boxplot() +
    theme_minimal() +
    ggtitle("Recall per method") +
    labs(x="IR method", y="Recall") +
    scale_fill_discrete(guide=FALSE)

ggsave("<pdf_image_file_name>.eps")