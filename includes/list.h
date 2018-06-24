#ifndef LIST_H_
#define LIST_H_

typedef struct List_s {
    void *data;
    struct List_s *next;
} List;

List* list_add_elem(List* list, void *elem);
List* list_merge(List* list, List *other);

#endif