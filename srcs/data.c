#include <stdio.h>

#include "data.h"

List* g_dict;
int** g_training_data;

void load_training(char *data_path) {
    printf("Loading Training data in \"%s\"\n", data_path);
}

void data_init(Arguments arguments) {
    if (arguments.action == TRAIN && arguments.data_dir_path != 0)
        load_training(arguments.data_dir_path);
}