#pragma once

#include <stdbool.h>
#include <stddef.h>

#ifndef LINKED_LIST_ELEMENT_TYPE_DEFINED
#define LINKED_LIST_ELEMENT_TYPE_DEFINED
typedef int EleType;
#endif

typedef struct CSListNode {
    EleType data;
    struct CSListNode *next;
} CSListNode;

CSListNode *cslist_init(void);

bool cslist_push_front(CSListNode *list, EleType value);
bool cslist_push_back(CSListNode *list, EleType value);
bool cslist_insert(CSListNode *list, size_t position, EleType value);

bool cslist_delete_at(CSListNode *list, size_t position);
bool cslist_delete_value(CSListNode *list, EleType value);
bool cslist_modify(CSListNode *list, size_t position, EleType value);

bool cslist_empty(const CSListNode *list);
size_t cslist_length(const CSListNode *list);
CSListNode *cslist_at(CSListNode *list, size_t position);
ptrdiff_t cslist_find(const CSListNode *list, EleType value);

void cslist_print(const CSListNode *list);
void cslist_clear(CSListNode *list);
void cslist_destroy(CSListNode **list);
