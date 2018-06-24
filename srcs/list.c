#include <stdlib.h>

#include "list.h"

List* list_add_elem(List* list, void *elem) {
    if (elem == 0 || list == 0)
        return list;
    List* elem_list = malloc(sizeof(List));
    elem_list->data = elem;
    elem_list->next = list;
    return elem_list;
}

List* list_merge(List* list, List *other) {
    if (other == 0 || list == 0)
        return list;
    List* tmp_list = list;
    while (tmp_list->next != 0)
        tmp_list = tmp_list->next;
    tmp_list->next = other;
    return list;
}

unsigned int list_len(List* list) {
    unsigned int count = 0;
    if (list == 0)
        return 0;
    ++count;
    while (list->next != 0) {
        list = list->next;
        ++count;
    }
    return count;
}