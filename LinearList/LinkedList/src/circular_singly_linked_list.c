#include "circular_singly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

static CSListNode *cslist_create_node(EleType value) {
    CSListNode *node = malloc(sizeof *node);
    if (node == NULL) {
        return NULL;
    }

    node->data = value;
    node->next = NULL;
    return node;
}

CSListNode *cslist_init(void) {
    CSListNode *list = cslist_create_node(0);
    if (list != NULL) {
        list->next = list;
    }
    return list;
}

bool cslist_push_front(CSListNode *list, EleType value) {
    if (list == NULL) {
        return false;
    }

    CSListNode *node = cslist_create_node(value);
    if (node == NULL) {
        return false;
    }

    node->next = list->next;
    list->next = node;
    return true;
}

bool cslist_push_back(CSListNode *list, EleType value) {
    if (list == NULL) {
        return false;
    }

    CSListNode *node = cslist_create_node(value);
    if (node == NULL) {
        return false;
    }

    CSListNode *tail = list;
    while (tail->next != list) {
        tail = tail->next;
    }

    node->next = list;
    tail->next = node;
    return true;
}

bool cslist_insert(CSListNode *list, size_t position, EleType value) {
    if (list == NULL) {
        return false;
    }

    CSListNode *previous = list;
    for (size_t i = 0; i < position; ++i) {
        if (previous->next == list) {
            return false;
        }
        previous = previous->next;
    }

    CSListNode *node = cslist_create_node(value);
    if (node == NULL) {
        return false;
    }

    node->next = previous->next;
    previous->next = node;
    return true;
}

bool cslist_delete_at(CSListNode *list, size_t position) {
    if (list == NULL) {
        return false;
    }

    CSListNode *previous = list;
    for (size_t i = 0; i < position; ++i) {
        if (previous->next == list) {
            return false;
        }
        previous = previous->next;
    }

    CSListNode *node = previous->next;
    if (node == list) {
        return false;
    }

    previous->next = node->next;
    free(node);
    return true;
}

bool cslist_delete_value(CSListNode *list, EleType value) {
    if (list == NULL) {
        return false;
    }

    CSListNode *previous = list;
    while (previous->next != list && previous->next->data != value) {
        previous = previous->next;
    }

    CSListNode *node = previous->next;
    if (node == list) {
        return false;
    }

    previous->next = node->next;
    free(node);
    return true;
}

bool cslist_modify(CSListNode *list, size_t position, EleType value) {
    CSListNode *node = cslist_at(list, position);
    if (node == NULL) {
        return false;
    }

    node->data = value;
    return true;
}

bool cslist_empty(const CSListNode *list) {
    return list == NULL || list->next == list;
}

size_t cslist_length(const CSListNode *list) {
    if (list == NULL) {
        return 0;
    }

    size_t length = 0;
    for (const CSListNode *node = list->next; node != list; node = node->next) {
        ++length;
    }
    return length;
}

CSListNode *cslist_at(CSListNode *list, size_t position) {
    if (list == NULL) {
        return NULL;
    }

    CSListNode *node = list->next;
    for (size_t i = 0; i < position; ++i) {
        if (node == list) {
            return NULL;
        }
        node = node->next;
    }

    return node == list ? NULL : node;
}

ptrdiff_t cslist_find(const CSListNode *list, EleType value) {
    if (list == NULL) {
        return -1;
    }

    ptrdiff_t position = 0;
    for (const CSListNode *node = list->next; node != list; node = node->next) {
        if (node->data == value) {
            return position;
        }
        ++position;
    }
    return -1;
}

void cslist_print(const CSListNode *list) {
    if (list == NULL) {
        return;
    }

    for (const CSListNode *node = list->next; node != list; node = node->next) {
        printf("%d ", node->data);
    }
    putchar('\n');
}

void cslist_clear(CSListNode *list) {
    if (list == NULL) {
        return;
    }

    CSListNode *node = list->next;
    while (node != list) {
        CSListNode *next = node->next;
        free(node);
        node = next;
    }
    list->next = list;
}

void cslist_destroy(CSListNode **list) {
    if (list == NULL || *list == NULL) {
        return;
    }

    cslist_clear(*list);
    free(*list);
    *list = NULL;
}
