#ifndef DATA_H_
#define DATA_H_

#include "list.h"
#include "arg.h"

typedef struct Dict_s {
    char *word;
    int value;
} Dict;

/**
 * Use to store tmp file data and ease the merge of all file.
 * Will be convert to two int**
 **/
typedef struct Training_Data_s {
    unsigned int* sentence;
    unsigned int* answer;
} Training_Data;

extern List* g_dict;
extern unsigned int** g_training_sentence;
extern unsigned int** g_training_answer;

void data_init(Arguments arguments);
void data_free(Arguments arguments);

#endif 