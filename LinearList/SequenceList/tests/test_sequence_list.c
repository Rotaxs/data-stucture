#include "sequence_list.h"
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

static void test_insert(void) {
    SequenceList *sqlist = sqlist_make();

    CHECK(sqlist != NULL);
    CHECK(sqlist_insert(sqlist, 0, 1));
    CHECK(sqlist_insert(sqlist, 0, 2));
    CHECK(sqlist->len == 2);
    CHECK(sqlist_insert(sqlist, 2, 3));
    CHECK(sqlist->len == 3);
    CHECK(sqlist->v[0] == 2 && sqlist->v[1] == 1 && sqlist->v[2] == 3);

    CHECK(!sqlist_insert(sqlist, 10, 0));
    CHECK(sqlist->len == 3);

    sqlist_free(sqlist);
}

static void test_delete(void) {
    SequenceList *sqlist = sqlist_make();

    CHECK(sqlist != NULL);

    sqlist->len = 3;
    sqlist->v[0] = 1;
    sqlist->v[1] = 2;
    sqlist->v[2] = 3;

    CHECK(sqlist_delete(sqlist, 1));
    CHECK(sqlist->len == 2);
    CHECK(sqlist->v[0] == 1 && sqlist->v[1] == 3);

    CHECK(!sqlist_delete(sqlist, 10));
    CHECK(sqlist->len == 2);
    CHECK(sqlist->v[0] == 1 && sqlist->v[1] == 3);

    sqlist_free(sqlist);
}

static void test_modify(void) {
    SequenceList *sqlist = sqlist_make();

    CHECK(sqlist != NULL);

    sqlist->len = 3;
    sqlist->v[0] = 1;
    sqlist->v[1] = 2;
    sqlist->v[2] = 3;

    CHECK(sqlist_modify(sqlist, 0, 100));
    CHECK(sqlist->len == 3);
    CHECK(sqlist->v[0] == 100 && sqlist->v[1] == 2 && sqlist->v[2] == 3);

    CHECK(!sqlist_modify(sqlist, 4, 100));
    CHECK(sqlist->len == 3);
    CHECK(sqlist->v[0] == 100 && sqlist->v[1] == 2 && sqlist->v[2] == 3);

    sqlist_free(sqlist);
}

static void test_query(void) {
    SequenceList *sqlist = sqlist_make();

    CHECK(sqlist != NULL);

    sqlist->len = 3;
    sqlist->v[0] = 1;
    sqlist->v[1] = 2;
    sqlist->v[2] = 3;

    CHECK(sqlist_query(sqlist, 1) == 0);
    CHECK(sqlist_query(sqlist, 2) == 1);
    CHECK(sqlist_query(sqlist, 3) == 2);

    sqlist_free(sqlist);
}

static void test_flip(void) {
    SequenceList *sqlist = sqlist_make();

    CHECK(sqlist != NULL);

    sqlist->len = 3;
    sqlist->v[0] = 1;
    sqlist->v[1] = 2;
    sqlist->v[2] = 3;

    CHECK(sqlist_flip(sqlist, 0, 2));
    CHECK(sqlist->v[0] == 3 && sqlist->v[1] == 2 && sqlist->v[2] == 1);

    sqlist_free(sqlist);
}

static void test_handswap(void) {
    SequenceList *sqlist = sqlist_make();

    CHECK(sqlist != NULL);

    sqlist->len = 6;
    sqlist->v[0] = 1;
    sqlist->v[1] = 2;
    sqlist->v[2] = 3;
    sqlist->v[3] = 4;
    sqlist->v[4] = 5;
    sqlist->v[5] = 6;

    CHECK(sqlist_handswap(sqlist, 0, 2, 5));
    CHECK(sqlist->v[0] == 4 && sqlist->v[1] == 5 && sqlist->v[2] == 6 && sqlist->v[3] == 1 &&
          sqlist->v[4] == 2 && sqlist->v[5] == 3);

    sqlist_free(sqlist);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <insert>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "insert") == 0) {
        test_insert();
    } else if (strcmp(argv[1], "delete") == 0) {
        test_delete();
    } else if (strcmp(argv[1], "modify") == 0) {
        test_modify();
    } else if (strcmp(argv[1], "query") == 0) {
        test_query();
    } else if (strcmp(argv[1], "flip") == 0) {
        test_flip();
    } else if (strcmp(argv[1], "handswap") == 0) {
        test_handswap();
    } else {
        fprintf(stderr, "Unkown test: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}