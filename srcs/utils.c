#include "utils.h"

char* string_concat(const char *str1, const char *str2)
{
    char *result = malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

char* string_trim(const char *input)
{
    char *result = malloc(strlen(input) + 1);
    int i, j = 0;
    for (i = 0; input[i] != '\0'; i++) {
        if (!isspace((unsigned char) input[i])) {
            result[j++] = input[i];
        }
    }
    result[j] = '\0';
    return result;
}

unsigned int string_nb_word(char *str) {
    char *tmp = malloc(strlen(str) + 1);
    tmp = strcpy(tmp, str);
    unsigned int count = 0;
    char *word = strtok(tmp," ,.!?");
    while (word != 0)
    {
        if (word[0] != '\n' && word[0] != '\r')
            ++count;
        word = strtok(0, " ,.!?");
    }
    return count;
}