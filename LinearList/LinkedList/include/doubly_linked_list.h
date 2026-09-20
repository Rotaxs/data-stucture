#pragma once

#include <stdbool.h>
#include <stddef.h>

#ifndef LINKED_LIST_ELEMENT_TYPE_DEFINED
#define LINKED_LIST_ELEMENT_TYPE_DEFINED
typedef int EleType;
#endif

/* Doubly linked list node. The list itself is represented by a dummy head node. */
typedef struct DListNode {
    EleType data;
    struct DListNode *prev;
    struct DListNode *next;
} DListNode;

DListNode *dlist_init(void);

bool dlist_push_front(DListNode *list, EleType value);
bool dlist_push_back(DListNode *list, EleType value);
bool dlist_insert(DListNode *list, size_t position, EleType value);

bool dlist_delete_at(DListNode *list, size_t position);
bool dlist_delete_value(DListNode *list, EleType value);
bool dlist_modify(DListNode *list, size_t position, EleType value);

bool dlist_empty(const DListNode *list);
size_t dlist_length(const DListNode *list);
DListNode *dlist_at(DListNode *list, size_t position);
ptrdiff_t dlist_find(const DListNode *list, EleType value);

void dlist_print(const DListNode *list);
void dlist_print_reverse(const DListNode *list);
void dlist_clear(DListNode *list);
void dlist_destroy(DListNode **list);
