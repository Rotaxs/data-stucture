#pragma once

#include <stdbool.h>
#include <stddef.h>

#ifndef LINKED_LIST_ELEMENT_TYPE_DEFINED
#define LINKED_LIST_ELEMENT_TYPE_DEFINED
typedef int EleType;
#endif

typedef struct CDListNode {
    EleType data;
    struct CDListNode *prev;
    struct CDListNode *next;
} CDListNode;

CDListNode *cdlist_init(void);

bool cdlist_push_front(CDListNode *list, EleType value);
bool cdlist_push_back(CDListNode *list, EleType value);
bool cdlist_insert(CDListNode *list, size_t position, EleType value);

bool cdlist_delete_at(CDListNode *list, size_t position);
bool cdlist_delete_value(CDListNode *list, EleType value);
bool cdlist_modify(CDListNode *list, size_t position, EleType value);

bool cdlist_empty(const CDListNode *list);
size_t cdlist_length(const CDListNode *list);
CDListNode *cdlist_at(CDListNode *list, size_t position);
ptrdiff_t cdlist_find(const CDListNode *list, EleType value);

void cdlist_print(const CDListNode *list);
void cdlist_print_reverse(const CDListNode *list);
void cdlist_clear(CDListNode *list);
void cdlist_destroy(CDListNode **list);
