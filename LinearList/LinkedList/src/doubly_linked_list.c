#include "doubly_linked_list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static DListNode *dlist_create_node(EleType value) {
    DListNode *node = (DListNode *)malloc(sizeof(DListNode));
    if (node == NULL) {
        return NULL;
    }
    node->next = NULL;
    node->prev = NULL;
    node->data = value;
    return node;
}

DListNode *dlist_init(void) {
    return dlist_create_node(0);
}

bool dlist_push_front(DListNode *list, EleType value) {
    if (list == NULL) {
        return false;
    }
    DListNode *node = dlist_create_node(value);
    if (node == NULL) {
        return false;
    }
    node->next = list->next;
    node->prev = list;
    if (list->next != NULL) {
        list->next->prev = node;
    }
    list->next = node;
    return true;
}

bool dlist_push_back(DListNode *list, EleType value) {
    if (list == NULL) {
        return false;
    }
    DListNode *node = dlist_create_node(value);
    if (node == NULL) {
        return false;
    }
    DListNode *tail;
    for (tail = list; tail->next; tail = tail->next) {
    }
    tail->next = node;
    node->prev = tail;
    return true;
}

bool dlist_insert(DListNode *list, size_t position, EleType value) {
    if (list == NULL) {
        return false;
    }
    DListNode *pre = list;
    for (size_t i = 0; i < position; ++i) {
        if (pre->next == NULL) {
            return false;
        }
        pre = pre->next;
    }
    DListNode *node = dlist_create_node(value);
    if (node == NULL) {
        return false;
    }
    node->next = pre->next;
    node->prev = pre;
    if (pre->next != NULL) {
        pre->next->prev = node;
    }
    pre->next = node;
    return true;
}

bool dlist_delete_at(DListNode *list, size_t position) {
    if (list == NULL) {
        return false;
    }
    DListNode *pre = list;
    for (size_t i = 0; i < position; ++i) {
        if (pre->next == NULL) {
            return false;
        }
        pre = pre->next;
    }
    if (pre->next == NULL) {
        return false;
    }
    DListNode *temp = pre->next;
    pre->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = pre;
    }
    free(temp);
    return true;
}

bool dlist_delete_value(DListNode *list, EleType value) {
    if (list == NULL) {
        return false;
    }
    DListNode *pre = list;
    for (; pre->next; pre = pre->next) {
        if (pre->next->data == value) {
            break;
        }
    }
    if (pre->next == NULL) {
        return false;
    }
    DListNode *temp = pre->next;
    pre->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = pre;
    }
    free(temp);
    return true;
}

bool dlist_modify(DListNode *list, size_t position, EleType value) {
    if (list == NULL) {
        return false;
    }
    DListNode *node = list->next;
    for (size_t i = 0; i < position; ++i) {
        if (node == NULL) {
            return false;
        }
        node = node->next;
    }
    if (node == NULL) {
        return false;
    }
    node->data = value;
    return true;
}

bool dlist_empty(const DListNode *list) {
    if (list == NULL) {
        return true;
    }
    return list->next == NULL;
}

size_t dlist_length(const DListNode *list) {
    if (list == NULL) {
        return 0;
    }
    size_t len = 0;
    for (DListNode *node = list->next; node; node = node->next) {
        ++len;
    }
    return len;
}

DListNode *dlist_at(DListNode *list, size_t position) {
    if (list == NULL) {
        return NULL;
    }
    DListNode *node = list->next;
    for (size_t i = 0; i < position; ++i) {
        if (node == NULL) {
            return NULL;
        }
        node = node->next;
    }
    return node;
}

ptrdiff_t dlist_find(const DListNode *list, EleType value) {
    if (list == NULL) {
        return -1;
    }
    ptrdiff_t pos = 0;
    for (DListNode *node = list->next; node; node = node->next) {
        if (node->data == value) {
            return pos;
        }
        ++pos;
    }
    return -1;
}

void dlist_print(const DListNode *list) {
    if (list == NULL) {
        return;
    }
    for (const DListNode *node = list->next; node; node = node->next) {
        printf("%d ", node->data);
    }
    putchar('\n');
}

void dlist_print_reverse(const DListNode *list) {
    if (list == NULL) {
        return;
    }
    const DListNode *tail = list;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    while (tail != list) {
        printf("%d ", tail->data);
        tail = tail->prev;
    }
    putchar('\n');
}

void dlist_clear(DListNode *list) {
    if (list == NULL) {
        return;
    }
    DListNode *node = list->next;
    while (node) {
        DListNode *temp = node;
        node = node->next;
        free(temp);
    }
    list->next = NULL;
}

void dlist_destroy(DListNode **list) {
    if (list == NULL) {
        return;
    }
    dlist_clear(*list);
    free(*list);
    *list = NULL;
}
