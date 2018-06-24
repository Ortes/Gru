#ifndef ARG_H_
#define ARG_H_

typedef enum Action_e{TRAIN, RUN, UNSET} Action;

typedef struct Arguments_s {
    Action action;
    char *data_dir_path;
    char *model_file_path;
} Arguments;

Arguments arguments_get_args(int argc, char* const argv[]);

#endif