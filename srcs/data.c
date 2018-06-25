#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

#include "data.h"
#include "utils.h"

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
    dict->word = malloc(strlen(word) + 1);
    strcpy(dict->word, word);
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

unsigned int find_word_in_dict(char *word) {
    List* tmp_dict = g_dict;
    while (tmp_dict->next != 0) {
        if (strcmp(((Dict*)tmp_dict->data)->word, word) == 0)
            return ((Dict*)tmp_dict->data)->value;
        tmp_dict = tmp_dict->next;
    }
    if (strcmp(((Dict*)tmp_dict->data)->word, word) == 0) {
        return ((Dict*)tmp_dict->data)->value;
    }
    Dict* dict_elem = create_dict_elem(word);
    g_dict = list_add_elem(g_dict, dict_elem);
    return dict_elem->value;
}

unsigned int* data_pchar_to_pint(char *str) {
    unsigned int index = 0;
    unsigned int* result = malloc(sizeof(unsigned int) * string_nb_word(str) + 1);
    char *word = strtok(str," ,.!?");
    while (word != 0)
    {
        if (word[0] != '\n' && word[0] != '\r')
            result[index++] == find_word_in_dict(word);
        word = strtok(0, " ,.!?");
    }
    result[index] = 0;
    return result;
}

List *load_training_file(FILE *file) {
    char *line = 0;
    size_t len = 0;
    ssize_t read;
    List *training_data = malloc(sizeof(List));
    unsigned int* last_sentence = malloc(sizeof(int));
    *last_sentence = 0;
    List *current_elem = training_data;
    List *prev_elem;
    int index = 0;

    while ((read = getline(&line, &len, file)) != -1) {
        unsigned int *sentence_value = data_pchar_to_pint(line);
        current_elem->data = create_training_data_elem(last_sentence, sentence_value);
        current_elem->next = malloc(sizeof(List));
        prev_elem = current_elem;
        current_elem = current_elem->next;
        last_sentence = sentence_value;
        index++;
        if (index % 1000 == 0)
            printf("\x1B[32m[INFO]\x1B[0m Process line : %d\n", index);
    }
    prev_elem->next = 0;
    printf("\x1B[32m[INFO]\x1B[0m Load a file of %d data\n", list_len(training_data));
    return training_data;
}

/**
 * Initialize all training global variable and start iterate over file to load training data.
 **/
void load_training(char *data_path) {
    printf("\x1B[32m[INFO]\x1B[0m Loading Training data in \"%s\"\n", data_path);
    init_dict();
    List *training_data_list = init_training_list();
    DIR* fd = 0;
    if (0 == (fd = opendir(data_path))) 
    {
        printf("\x1B[31m[ERROR]\x1B[0m : Failed to open input directory - %s\n", strerror(errno));
        return;
    }
    struct dirent* direntry;
    while ((direntry = readdir(fd))) 
    {
        if (!strcmp(direntry->d_name, ".") || !strcmp(direntry->d_name, ".."))
            continue;
        char *file_path;
        if(data_path[strlen(data_path)-1] == '/')
            file_path = string_concat(data_path, direntry->d_name);
        else
        {
            file_path = string_concat(data_path, "/");
            file_path = string_concat(file_path, direntry->d_name);
        }
        FILE *entry_file = fopen(file_path, "r");
        if (entry_file == 0)
        {
            printf("\x1B[31m[ERROR]\x1B[0m : Failed to open entry file - %s\n", strerror(errno));
            continue;
        }
        printf("\x1B[32m[INFO]\x1B[0m Loading File \"%s\"\n", direntry->d_name);
        training_data_list = list_merge(load_training_file(entry_file), training_data_list);

        free(file_path);
        fclose(entry_file);
    }
    printf("\x1B[32m[INFO]\x1B[0m End of loading. Size of Global Word Dictionnary %d. Size of data %d\n", list_len(g_dict), list_len(training_data_list));
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
    printf("\x1B[32m[INFO]\x1B[0m Unloading data\n");
    if (arguments.action == TRAIN && arguments.data_dir_path != 0)
        free_training();
}