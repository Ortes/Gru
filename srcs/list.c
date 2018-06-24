#include "list.h"

List* list_add_elem(List* list, List *elem) {
    if (elem == 0)
        return
    elem->next = list;
    return elem;
}