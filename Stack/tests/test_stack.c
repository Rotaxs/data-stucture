#include "linked_stack.h"
#include "sequential_stack.h"
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

static void check_sqstack(SequentialStack *stack, size_t count, EleType top) {
    CHECK(stack != NULL);
    CHECK(sqstack_size(stack) == count);
    CHECK(sqstack_empty(stack) == (count == 0));
    CHECK(sqstack_full(stack) == (count == STACK_MAX_SIZE));
    CHECK(sqstack_top(stack) == top);
    CHECK(sqstack_top(stack) == top);
    CHECK(sqstack_size(stack) == count);
}

static void test_sqstack_null(void) {
    CHECK(!sqstack_push(NULL, 1));
    CHECK(!sqstack_pop(NULL));
    CHECK(!sqstack_clear(NULL));
    CHECK(sqstack_top(NULL) == 0);
    CHECK(sqstack_size(NULL) == 0);
    CHECK(sqstack_empty(NULL));
    CHECK(!sqstack_full(NULL));
}

static void test_sqstack_lifo(void) {
    SequentialStack *stack = sqstack_init();
    check_sqstack(stack, 0, 0);
    CHECK(!sqstack_pop(stack));
    check_sqstack(stack, 0, 0);
    CHECK(sqstack_clear(stack));
    check_sqstack(stack, 0, 0);

    const EleType values[] = {1, 0, -7, -7, 42};
    const size_t count = sizeof(values) / sizeof(values[0]);
    for (size_t i = 0; i < count; ++i) {
        CHECK(sqstack_push(stack, values[i]));
        check_sqstack(stack, i + 1, values[i]);
    }

    for (size_t i = count; i > 0; --i) {
        CHECK(sqstack_top(stack) == values[i - 1]);
        CHECK(sqstack_pop(stack));
        check_sqstack(stack, i - 1, i > 1 ? values[i - 2] : 0);
    }
    CHECK(!sqstack_pop(stack));
    check_sqstack(stack, 0, 0);

    CHECK(sqstack_push(stack, 8));
    check_sqstack(stack, 1, 8);
    CHECK(sqstack_pop(stack));
    check_sqstack(stack, 0, 0);
    free(stack);
}

static void test_sqstack_capacity(void) {
    SequentialStack *stack = sqstack_init();
    check_sqstack(stack, 0, 0);

    for (int i = 0; i < STACK_MAX_SIZE; ++i) {
        CHECK(sqstack_push(stack, i + 1));
        check_sqstack(stack, (size_t)i + 1, i + 1);
    }

    CHECK(!sqstack_push(stack, -1));
    check_sqstack(stack, STACK_MAX_SIZE, STACK_MAX_SIZE);
    CHECK(!sqstack_push(stack, -2));
    check_sqstack(stack, STACK_MAX_SIZE, STACK_MAX_SIZE);

    CHECK(sqstack_pop(stack));
    check_sqstack(stack, STACK_MAX_SIZE - 1, STACK_MAX_SIZE - 1);
    CHECK(sqstack_push(stack, -3));
    check_sqstack(stack, STACK_MAX_SIZE, -3);
    CHECK(!sqstack_push(stack, -4));
    check_sqstack(stack, STACK_MAX_SIZE, -3);
    CHECK(sqstack_pop(stack));

    for (int i = STACK_MAX_SIZE - 1; i > 0; --i) {
        check_sqstack(stack, (size_t)i, i);
        CHECK(sqstack_pop(stack));
    }
    check_sqstack(stack, 0, 0);
    CHECK(!sqstack_pop(stack));
    check_sqstack(stack, 0, 0);
    free(stack);
}

static void test_sqstack_clear_reuse(void) {
    SequentialStack *stack = sqstack_init();
    check_sqstack(stack, 0, 0);

    CHECK(sqstack_push(stack, 10));
    CHECK(sqstack_push(stack, 20));
    CHECK(sqstack_clear(stack));
    check_sqstack(stack, 0, 0);
    CHECK(!sqstack_pop(stack));
    CHECK(sqstack_clear(stack));
    check_sqstack(stack, 0, 0);

    for (int round = 0; round < 2; ++round) {
        for (int i = 0; i < STACK_MAX_SIZE; ++i) {
            CHECK(sqstack_push(stack, i + 1));
        }
        check_sqstack(stack, STACK_MAX_SIZE, STACK_MAX_SIZE);
        CHECK(!sqstack_push(stack, -1));
        CHECK(sqstack_clear(stack));
        check_sqstack(stack, 0, 0);
        CHECK(!sqstack_pop(stack));
    }

    CHECK(sqstack_push(stack, -9));
    check_sqstack(stack, 1, -9);
    CHECK(sqstack_pop(stack));
    check_sqstack(stack, 0, 0);
    free(stack);
}

static void test_sqstack(void) {
    test_sqstack_null();
    test_sqstack_lifo();
    test_sqstack_capacity();
    test_sqstack_clear_reuse();
}

static void check_ltstack(LinkedStack *stack, size_t count, EleType top) {
    CHECK(stack != NULL);
    CHECK(ltstack_size(stack) == count);
    CHECK(ltstack_empty(stack) == (count == 0));
    CHECK(ltstack_top(stack) == top);
    /* Reading the top must not remove an element. */
    CHECK(ltstack_top(stack) == top);
    CHECK(ltstack_size(stack) == count);
}

static void test_ltstack_null(void) {
    CHECK(!ltstack_push(NULL, 1));
    CHECK(!ltstack_pop(NULL));
    CHECK(!ltstack_clear(NULL));
    CHECK(!ltstack_destroy(NULL));
    CHECK(ltstack_top(NULL) == 0);
    CHECK(ltstack_size(NULL) == 0);
    CHECK(ltstack_empty(NULL));
}

static void test_ltstack_lifo(void) {
    LinkedStack *stack = ltstack_init();
    check_ltstack(stack, 0, 0);
    CHECK(!ltstack_pop(stack));
    check_ltstack(stack, 0, 0);
    CHECK(ltstack_clear(stack));
    check_ltstack(stack, 0, 0);

    const EleType values[] = {1, 0, -7, -7, 42};
    const size_t count = sizeof(values) / sizeof(values[0]);
    for (size_t i = 0; i < count; ++i) {
        CHECK(ltstack_push(stack, values[i]));
        check_ltstack(stack, i + 1, values[i]);
    }

    CHECK(ltstack_pop(stack));
    check_ltstack(stack, count - 1, values[count - 2]);
    CHECK(ltstack_push(stack, 99));
    check_ltstack(stack, count, 99);
    CHECK(ltstack_pop(stack));
    CHECK(ltstack_push(stack, values[count - 1]));

    for (size_t i = count; i > 0; --i) {
        CHECK(ltstack_top(stack) == values[i - 1]);
        CHECK(ltstack_pop(stack));
        check_ltstack(stack, i - 1, i > 1 ? values[i - 2] : 0);
    }
    CHECK(!ltstack_pop(stack));
    check_ltstack(stack, 0, 0);
    CHECK(ltstack_push(stack, 8));
    check_ltstack(stack, 1, 8);
    CHECK(ltstack_pop(stack));
    check_ltstack(stack, 0, 0);
    CHECK(ltstack_destroy(stack));
}

static void test_ltstack_growth(void) {
    LinkedStack *stack = ltstack_init();
    check_ltstack(stack, 0, 0);

    const int count = STACK_MAX_SIZE + 100;
    for (int i = 0; i < count; ++i) {
        CHECK(ltstack_push(stack, i + 1));
        check_ltstack(stack, (size_t)i + 1, i + 1);
    }
    for (int i = count; i > 0; --i) {
        check_ltstack(stack, (size_t)i, i);
        CHECK(ltstack_pop(stack));
    }
    check_ltstack(stack, 0, 0);
    CHECK(!ltstack_pop(stack));
    check_ltstack(stack, 0, 0);
    CHECK(ltstack_destroy(stack));
}

static void test_ltstack_clear_reuse(void) {
    LinkedStack *stack = ltstack_init();
    check_ltstack(stack, 0, 0);

    for (int round = 0; round < 3; ++round) {
        for (int i = 0; i < 100; ++i) {
            CHECK(ltstack_push(stack, i + 1));
        }
        check_ltstack(stack, 100, 100);
        CHECK(ltstack_clear(stack));
        check_ltstack(stack, 0, 0);
        CHECK(!ltstack_pop(stack));
        check_ltstack(stack, 0, 0);
        CHECK(ltstack_clear(stack));
        check_ltstack(stack, 0, 0);

        CHECK(ltstack_push(stack, -9));
        check_ltstack(stack, 1, -9);
        CHECK(ltstack_pop(stack));
        check_ltstack(stack, 0, 0);
    }
    CHECK(ltstack_destroy(stack));
}

static void test_ltstack_destroy(void) {
    LinkedStack *stack = ltstack_init();
    check_ltstack(stack, 0, 0);
    CHECK(ltstack_destroy(stack));

    stack = ltstack_init();
    check_ltstack(stack, 0, 0);
    CHECK(ltstack_push(stack, 1));
    CHECK(ltstack_push(stack, 2));
    CHECK(ltstack_push(stack, 3));
    check_ltstack(stack, 3, 3);
    CHECK(ltstack_destroy(stack));
}

static void test_ltstack(void) {
    test_ltstack_null();
    test_ltstack_lifo();
    test_ltstack_growth();
    test_ltstack_clear_reuse();
    test_ltstack_destroy();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <sequential|list>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "sequential") == 0) {
        test_sqstack();
    } else if (strcmp(argv[1], "list") == 0) {
        test_ltstack();
    } else {
        fprintf(stderr, "Unknown test: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    return 0;
}
