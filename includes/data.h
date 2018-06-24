#ifndef DATA_H_
#define DATA_H_

#include "list.h"
#include "arg.h"

typedef struct Dict_s {
    char *word;
    int value;
} Dict;

extern List* g_dict;
extern int** g_training_data;

void data_init(Arguments arguments);

#endif