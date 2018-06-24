#ifndef UTILS_H_
#define UTILS_H_

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

char* string_concat(const char *str1, const char *str2);
char* string_trim(const char *input);
unsigned int string_nb_word(char *str);

#endif