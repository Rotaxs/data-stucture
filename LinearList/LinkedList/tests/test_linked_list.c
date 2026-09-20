#include "circular_doubly_linked_list.h"
#include "circular_singly_linked_list.h"
#include "doubly_linked_list.h"
#include "singly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK(condition)                                                                           \
    do {                                                                                           \
        if (!(condition)) {                                                                        \
            fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #condition);                        \
            exit(EXIT_FAILURE);                                                                    \
        }                                                                                          \
    } while (0)

static void check_slist(const SListNode *list, const EleType values[], size_t count) {
    CHECK(list != NULL);
    CHECK(slist_length(list) == count);
    CHECK(slist_empty(list) == (count == 0));

    const SListNode *node = list->next;
    for (size_t i = 0; i < count; ++i) {
        CHECK(node != NULL);
        CHECK(node->data == values[i]);
        node = node->next;
    }
    CHECK(node == NULL);
}

static void check_dlist(const DListNode *list, const EleType values[], size_t count) {
    CHECK(list != NULL);
    CHECK(dlist_length(list) == count);
    CHECK(dlist_empty(list) == (count == 0));

    const DListNode *previous = list;
    const DListNode *node = list->next;
    for (size_t i = 0; i < count; ++i) {
        CHECK(node != NULL);
        CHECK(node->data == values[i]);
        CHECK(node->prev == previous);
        previous = node;
        node = node->next;
    }
    CHECK(node == NULL);
}

static void check_cslist(const CSListNode *list, const EleType values[], size_t count) {
    CHECK(list != NULL);
    CHECK(cslist_length(list) == count);
    CHECK(cslist_empty(list) == (count == 0));

    const CSListNode *node = list->next;
    for (size_t i = 0; i < count; ++i) {
        CHECK(node != list);
        CHECK(node->data == values[i]);
        node = node->next;
    }
    CHECK(node == list);
}

static void check_cdlist(const CDListNode *list, const EleType values[], size_t count) {
    CHECK(list != NULL);
    CHECK(cdlist_length(list) == count);
    CHECK(cdlist_empty(list) == (count == 0));
    CHECK(list->next->prev == list);
    CHECK(list->prev->next == list);

    const CDListNode *node = list->next;
    for (size_t i = 0; i < count; ++i) {
        CHECK(node != list);
        CHECK(node->data == values[i]);
        CHECK(node->next->prev == node);
        CHECK(node->prev->next == node);
        node = node->next;
    }
    CHECK(node == list);

    node = list->prev;
    for (size_t i = count; i > 0; --i) {
        CHECK(node != list);
        CHECK(node->data == values[i - 1]);
        node = node->prev;
    }
    CHECK(node == list);
}

static void test_singly(void) {
    CHECK(slist_empty(NULL));
    CHECK(slist_length(NULL) == 0);
    CHECK(slist_at(NULL, 0) == NULL);
    CHECK(slist_find(NULL, 1) == -1);
    CHECK(!slist_push_front(NULL, 1));

    SListNode *list = slist_init();
    const EleType empty[] = {0};
    check_slist(list, empty, 0);
    CHECK(!slist_delete_at(list, 0));
    CHECK(!slist_delete_value(list, 1));

    CHECK(slist_push_back(list, 20));
    CHECK(slist_push_front(list, 10));
    CHECK(slist_insert(list, 1, 15));
    CHECK(slist_insert(list, 3, 30));
    CHECK(!slist_insert(list, 5, 40));
    const EleType inserted[] = {10, 15, 20, 30};
    check_slist(list, inserted, 4);

    CHECK(slist_at(list, 0)->data == 10);
    CHECK(slist_at(list, 3)->data == 30);
    CHECK(slist_at(list, 4) == NULL);
    CHECK(slist_find(list, 20) == 2);
    CHECK(slist_find(list, 99) == -1);
    CHECK(slist_modify(list, 2, 21));
    CHECK(!slist_modify(list, 4, 0));

    CHECK(slist_delete_at(list, 0));
    CHECK(slist_delete_value(list, 30));
    CHECK(slist_delete_at(list, 1));
    CHECK(!slist_delete_at(list, 1));
    const EleType remaining[] = {15};
    check_slist(list, remaining, 1);

    slist_clear(list);
    check_slist(list, empty, 0);
    CHECK(slist_push_back(list, 7));
    slist_destroy(&list);
    CHECK(list == NULL);
    slist_destroy(&list);
}

static void test_doubly(void) {
    CHECK(dlist_empty(NULL));
    CHECK(dlist_length(NULL) == 0);
    CHECK(dlist_at(NULL, 0) == NULL);
    CHECK(dlist_find(NULL, 1) == -1);
    CHECK(!dlist_push_back(NULL, 1));

    DListNode *list = dlist_init();
    const EleType empty[] = {0};
    check_dlist(list, empty, 0);
    CHECK(!dlist_delete_at(list, 0));
    CHECK(!dlist_delete_value(list, 1));

    CHECK(dlist_push_back(list, 20));
    CHECK(dlist_push_front(list, 10));
    CHECK(dlist_insert(list, 1, 15));
    CHECK(dlist_insert(list, 3, 30));
    CHECK(!dlist_insert(list, 5, 40));
    const EleType inserted[] = {10, 15, 20, 30};
    check_dlist(list, inserted, 4);

    CHECK(dlist_at(list, 0)->data == 10);
    CHECK(dlist_at(list, 3)->data == 30);
    CHECK(dlist_at(list, 4) == NULL);
    CHECK(dlist_find(list, 20) == 2);
    CHECK(dlist_find(list, 99) == -1);
    CHECK(dlist_modify(list, 2, 21));
    CHECK(!dlist_modify(list, 4, 0));

    CHECK(dlist_delete_at(list, 0));
    CHECK(dlist_delete_value(list, 30));
    CHECK(dlist_delete_at(list, 1));
    CHECK(!dlist_delete_at(list, 1));
    const EleType remaining[] = {15};
    check_dlist(list, remaining, 1);

    dlist_clear(list);
    check_dlist(list, empty, 0);
    CHECK(dlist_push_front(list, 7));
    dlist_destroy(&list);
    CHECK(list == NULL);
    dlist_destroy(&list);
}

static void test_circular_singly(void) {
    CHECK(cslist_empty(NULL));
    CHECK(cslist_length(NULL) == 0);
    CHECK(cslist_at(NULL, 0) == NULL);
    CHECK(cslist_find(NULL, 1) == -1);
    CHECK(!cslist_push_front(NULL, 1));

    CSListNode *list = cslist_init();
    const EleType empty[] = {0};
    check_cslist(list, empty, 0);
    CHECK(!cslist_delete_at(list, 0));
    CHECK(!cslist_delete_value(list, 1));

    CHECK(cslist_push_back(list, 20));
    CHECK(cslist_push_front(list, 10));
    CHECK(cslist_insert(list, 1, 15));
    CHECK(cslist_insert(list, 3, 30));
    CHECK(!cslist_insert(list, 5, 40));
    const EleType inserted[] = {10, 15, 20, 30};
    check_cslist(list, inserted, 4);

    CHECK(cslist_at(list, 0)->data == 10);
    CHECK(cslist_at(list, 3)->data == 30);
    CHECK(cslist_at(list, 4) == NULL);
    CHECK(cslist_find(list, 20) == 2);
    CHECK(cslist_find(list, 99) == -1);
    CHECK(cslist_modify(list, 2, 21));
    CHECK(!cslist_modify(list, 4, 0));

    CHECK(cslist_delete_at(list, 0));
    CHECK(cslist_delete_value(list, 30));
    CHECK(cslist_delete_at(list, 1));
    CHECK(!cslist_delete_at(list, 1));
    const EleType remaining[] = {15};
    check_cslist(list, remaining, 1);

    cslist_clear(list);
    check_cslist(list, empty, 0);
    CHECK(cslist_push_back(list, 7));
    cslist_destroy(&list);
    CHECK(list == NULL);
    cslist_destroy(&list);
}

static void test_circular_doubly(void) {
    CHECK(cdlist_empty(NULL));
    CHECK(cdlist_length(NULL) == 0);
    CHECK(cdlist_at(NULL, 0) == NULL);
    CHECK(cdlist_find(NULL, 1) == -1);
    CHECK(!cdlist_push_back(NULL, 1));

    CDListNode *list = cdlist_init();
    const EleType empty[] = {0};
    check_cdlist(list, empty, 0);
    CHECK(!cdlist_delete_at(list, 0));
    CHECK(!cdlist_delete_value(list, 1));

    CHECK(cdlist_push_back(list, 20));
    CHECK(cdlist_push_front(list, 10));
    CHECK(cdlist_insert(list, 1, 15));
    CHECK(cdlist_insert(list, 3, 30));
    CHECK(!cdlist_insert(list, 5, 40));
    const EleType inserted[] = {10, 15, 20, 30};
    check_cdlist(list, inserted, 4);

    CHECK(cdlist_at(list, 0)->data == 10);
    CHECK(cdlist_at(list, 3)->data == 30);
    CHECK(cdlist_at(list, 4) == NULL);
    CHECK(cdlist_find(list, 20) == 2);
    CHECK(cdlist_find(list, 99) == -1);
    CHECK(cdlist_modify(list, 2, 21));
    CHECK(!cdlist_modify(list, 4, 0));

    CHECK(cdlist_delete_at(list, 0));
    CHECK(cdlist_delete_value(list, 30));
    CHECK(cdlist_delete_at(list, 1));
    CHECK(!cdlist_delete_at(list, 1));
    const EleType remaining[] = {15};
    check_cdlist(list, remaining, 1);

    cdlist_clear(list);
    check_cdlist(list, empty, 0);
    CHECK(cdlist_push_front(list, 7));
    cdlist_destroy(&list);
    CHECK(list == NULL);
    cdlist_destroy(&list);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr,
                "Usage: %s <singly|doubly|circular_singly|circular_doubly>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "singly") == 0) {
        test_singly();
    } else if (strcmp(argv[1], "doubly") == 0) {
        test_doubly();
    } else if (strcmp(argv[1], "circular_singly") == 0) {
        test_circular_singly();
    } else if (strcmp(argv[1], "circular_doubly") == 0) {
        test_circular_doubly();
    } else {
        fprintf(stderr, "Unknown test: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
