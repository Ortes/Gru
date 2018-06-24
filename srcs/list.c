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
    while (list->next != 0)
        list = list->next;
    list->next = other;
    return list;
}