#include "circular_doubly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

static CDListNode *cdlist_create_node(EleType value) {
    CDListNode *node = malloc(sizeof *node);
    if (node == NULL) {
        return NULL;
    }

    node->data = value;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

CDListNode *cdlist_init(void) {
    CDListNode *list = cdlist_create_node(0);
    if (list != NULL) {
        list->prev = list;
        list->next = list;
    }
    return list;
}

bool cdlist_push_front(CDListNode *list, EleType value) {
    if (list == NULL) {
        return false;
    }

    CDListNode *node = cdlist_create_node(value);
    if (node == NULL) {
        return false;
    }

    node->prev = list;
    node->next = list->next;
    list->next->prev = node;
    list->next = node;
    return true;
}

bool cdlist_push_back(CDListNode *list, EleType value) {
    if (list == NULL) {
        return false;
    }

    CDListNode *node = cdlist_create_node(value);
    if (node == NULL) {
        return false;
    }

    node->prev = list->prev;
    node->next = list;
    list->prev->next = node;
    list->prev = node;
    return true;
}

bool cdlist_insert(CDListNode *list, size_t position, EleType value) {
    if (list == NULL) {
        return false;
    }

    CDListNode *previous = list;
    for (size_t i = 0; i < position; ++i) {
        if (previous->next == list) {
            return false;
        }
        previous = previous->next;
    }

    CDListNode *node = cdlist_create_node(value);
    if (node == NULL) {
        return false;
    }

    node->prev = previous;
    node->next = previous->next;
    previous->next->prev = node;
    previous->next = node;
    return true;
}

bool cdlist_delete_at(CDListNode *list, size_t position) {
    if (list == NULL) {
        return false;
    }

    CDListNode *previous = list;
    for (size_t i = 0; i < position; ++i) {
        if (previous->next == list) {
            return false;
        }
        previous = previous->next;
    }

    CDListNode *node = previous->next;
    if (node == list) {
        return false;
    }

    previous->next = node->next;
    node->next->prev = previous;
    free(node);
    return true;
}

bool cdlist_delete_value(CDListNode *list, EleType value) {
    if (list == NULL) {
        return false;
    }

    CDListNode *node = list->next;
    while (node != list && node->data != value) {
        node = node->next;
    }

    if (node == list) {
        return false;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    return true;
}

bool cdlist_modify(CDListNode *list, size_t position, EleType value) {
    CDListNode *node = cdlist_at(list, position);
    if (node == NULL) {
        return false;
    }

    node->data = value;
    return true;
}

bool cdlist_empty(const CDListNode *list) {
    return list == NULL || list->next == list;
}

size_t cdlist_length(const CDListNode *list) {
    if (list == NULL) {
        return 0;
    }

    size_t length = 0;
    for (const CDListNode *node = list->next; node != list; node = node->next) {
        ++length;
    }
    return length;
}

CDListNode *cdlist_at(CDListNode *list, size_t position) {
    if (list == NULL) {
        return NULL;
    }

    CDListNode *node = list->next;
    for (size_t i = 0; i < position; ++i) {
        if (node == list) {
            return NULL;
        }
        node = node->next;
    }

    return node == list ? NULL : node;
}

ptrdiff_t cdlist_find(const CDListNode *list, EleType value) {
    if (list == NULL) {
        return -1;
    }

    ptrdiff_t position = 0;
    for (const CDListNode *node = list->next; node != list; node = node->next) {
        if (node->data == value) {
            return position;
        }
        ++position;
    }
    return -1;
}

void cdlist_print(const CDListNode *list) {
    if (list == NULL) {
        return;
    }

    for (const CDListNode *node = list->next; node != list; node = node->next) {
        printf("%d ", node->data);
    }
    putchar('\n');
}

void cdlist_print_reverse(const CDListNode *list) {
    if (list == NULL) {
        return;
    }

    for (const CDListNode *node = list->prev; node != list; node = node->prev) {
        printf("%d ", node->data);
    }
    putchar('\n');
}

void cdlist_clear(CDListNode *list) {
    if (list == NULL) {
        return;
    }

    CDListNode *node = list->next;
    while (node != list) {
        CDListNode *next = node->next;
        free(node);
        node = next;
    }
    list->next = list;
    list->prev = list;
}

void cdlist_destroy(CDListNode **list) {
    if (list == NULL || *list == NULL) {
        return;
    }

    cdlist_clear(*list);
    free(*list);
    *list = NULL;
}
