#include <stdio.h>
#include <stdlib.h>

#include "data.h"

/**
 * The Global Dictionnary of word (Dict in dict.h)
 **/
List* g_dict;
unsigned int g_dict_index = 0; // contains the last word index + 1.

/**
 * Two int** of training data one for sentence, another for answer
 **/
unsigned int** g_training_sentence;
unsigned int** g_training_answer;

/**
 * Create a Dictionnary element.
 **/
Dict* create_dict_elem(char* word) {
    Dict* dict = malloc(sizeof(Dict));
    dict->word = word;
    dict->value = g_dict_index;
    ++g_dict_index;
    return dict;
}

/**
 * Create a Training data element (sentence and answer).
 **/
Training_Data* create_training_data_elem(unsigned int* sentence, unsigned int* answer) {
    Training_Data* training_data = malloc(sizeof(Training_Data));
    training_data->sentence = sentence;
    training_data->answer = answer;
    return training_data;
}

/**
 * Initialize the Global dictionary of word.
 **/
void init_dict() {
    g_dict = malloc(sizeof(List));
    g_dict->data = create_dict_elem("");
    g_dict->next = 0;
}

/**
 * Initialize the training list. This list ease the merge of all data file.
 * Will be convert to two int** later in program.
 **/
List* init_training_list() {
    List *training_data = malloc(sizeof(List));
    unsigned int* init_value = malloc(sizeof(int));
    *init_value = 0;
    training_data->data = create_training_data_elem(init_value, init_value);
    training_data->next = 0;
    return training_data;
}

/**
 * Initialize all training global variable and start iterate over file to load training data.
 **/
void load_training(char *data_path) {
    printf("Loading Training data in \"%s\"\n", data_path);
    init_dict();
    List *training_data_list = init_training_list();
}

/**
 * Function call in main to initialize all data.
 **/
void data_init(Arguments arguments) {
    if (arguments.action == TRAIN && arguments.data_dir_path != 0)
        load_training(arguments.data_dir_path);
}

/**
 * Free all training data.
 **/
void free_training() {
    while (g_dict->next != 0) {
        List* tmp = g_dict;
        g_dict = g_dict->next;
        free(tmp->data);
        free(tmp);
    }
    free(g_dict->data);
    free(g_dict);
}

/**
 * Free all data at the end of program.
 */
void data_free(Arguments arguments) {
    printf("Unloading data\n");
    if (arguments.action == TRAIN && arguments.data_dir_path != 0)
        free_training();
}