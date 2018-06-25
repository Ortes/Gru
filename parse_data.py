with open("./data/training/conv-4.csv") as f:
    with open("./data/training/conv-4.data", "w") as f1:
        for line in f:
            outline = line.split(";")[-1]
            outline = outline.replace("\"", "")
            f1.write(outline) 