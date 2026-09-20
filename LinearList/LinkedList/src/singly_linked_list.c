#include "singly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

static SListNode *slist_create_node(EleType value) {
    SListNode *node = (SListNode *)malloc(sizeof(SListNode));
    if (node == NULL) {
        return NULL;
    }
    node->next = NULL;
    node->data = value;
    return node;
}

SListNode *slist_init(void) {
    return slist_create_node(0);
}

bool slist_push_front(SListNode *list, EleType value) {
    if (list == NULL) {
        return false;
    }
    SListNode *node = slist_create_node(value);
    if (node == NULL) {
        return false;
    }
    node->next = list->next;
    list->next = node;
    return true;
}

bool slist_push_back(SListNode *list, EleType value) {
    if (list == NULL) {
        return false;
    }
    SListNode *node = slist_create_node(value);
    if (node == NULL) {
        return false;
    }
    SListNode *tail;
    for (tail = list; tail->next; tail = tail->next) {
    }
    tail->next = node;
    return true;
}

bool slist_insert(SListNode *list, size_t position, EleType value) {
    if (list == NULL) {
        return false;
    }
    SListNode *pre = list;
    for (size_t i = 0; i < position; ++i) {
        if (pre->next == NULL) {
            return false;
        }
        pre = pre->next;
    }
    SListNode *node = slist_create_node(value);
    if (node == NULL) {
        return false;
    }
    node->next = pre->next;
    pre->next = node;
    return true;
}

bool slist_delete_at(SListNode *list, size_t position) {
    if (list == NULL) {
        return false;
    }
    SListNode *pre = list;
    for (size_t i = 0; i < position; ++i) {
        if (pre->next == NULL) {
            return false;
        }
        pre = pre->next;
    }
    if (pre->next == NULL) {
        return false;
    }
    SListNode *node_del = pre->next;
    pre->next = pre->next->next;
    free(node_del);
    return true;
}

bool slist_delete_value(SListNode *list, EleType value) {
    if (list == NULL) {
        return false;
    }
    SListNode *pre = list;
    while (pre->next != NULL) {
        if (pre->next->data == value) {
            break;
        }
        pre = pre->next;
    }
    if (pre->next == NULL) {
        return false;
    }
    SListNode *node_del = pre->next;
    pre->next = pre->next->next;
    free(node_del);
    return true;
}

bool slist_modify(SListNode *list, size_t position, EleType value) {
    if (list == NULL) {
        return false;
    }
    SListNode *node = list->next;
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

bool slist_empty(const SListNode *list) {
    if (list == NULL) {
        return true;
    }
    return list->next == NULL;
}

size_t slist_length(const SListNode *list) {
    if (list == NULL) {
        return 0;
    }
    size_t len = 0;
    for (SListNode *node = list->next; node; node = node->next) {
        ++len;
    }
    return len;
}

SListNode *slist_at(SListNode *list, size_t position) {
    if (list == NULL) {
        return NULL;
    }
    SListNode *node = list->next;
    for (size_t i = 0; i < position; ++i) {
        if (node == NULL) {
            return NULL;
        }
        node = node->next;
    }
    return node;
}

ptrdiff_t slist_find(const SListNode *list, EleType value) {
    if (list == NULL) {
        return -1;
    }
    SListNode *node = list->next;
    ptrdiff_t pos = 0;
    for (; node; node = node->next) {
        if (node->data == value) {
            return pos;
        }
        ++pos;
    }
    return -1;
}

void slist_print(const SListNode *list) {
    if (list == NULL) {
        return;
    }
    SListNode *node = list->next;
    for (; node; node = node->next) {
        printf("%d ", node->data);
    }
    putchar('\n');
}

void slist_clear(SListNode *list) {
    if (list == NULL) {
        return;
    }
    SListNode *node = list->next;
    while (node != NULL) {
        SListNode *next = node->next;
        free(node);
        node = next;
    }
    list->next = NULL;
}

void slist_destroy(SListNode **list) {
    if (list == NULL || *list == NULL) {
        return;
    }
    slist_clear(*list);
    free(*list);
    *list = NULL;
}
