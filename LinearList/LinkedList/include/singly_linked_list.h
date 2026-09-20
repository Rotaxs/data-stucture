#pragma once

#include <stdbool.h>
#include <stddef.h>

#ifndef LINKED_LIST_ELEMENT_TYPE_DEFINED
#define LINKED_LIST_ELEMENT_TYPE_DEFINED
typedef int EleType;
#endif

typedef struct SListNode {
    EleType data;
    struct SListNode *next;
} SListNode;

SListNode *slist_init(void);

bool slist_push_front(SListNode *list, EleType value);
bool slist_push_back(SListNode *list, EleType value);
bool slist_insert(SListNode *list, size_t position, EleType value);

bool slist_delete_at(SListNode *list, size_t position);
bool slist_delete_value(SListNode *list, EleType value);
bool slist_modify(SListNode *list, size_t position, EleType value);

bool slist_empty(const SListNode *list);
size_t slist_length(const SListNode *list);
SListNode *slist_at(SListNode *list, size_t position);
ptrdiff_t slist_find(const SListNode *list, EleType value);

void slist_print(const SListNode *list);
void slist_clear(SListNode *list);
void slist_destroy(SListNode **list);
