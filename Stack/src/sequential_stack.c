#include "sequential_stack.h"
#include <stdlib.h>

SequentialStack *sqstack_init(void) {
    SequentialStack *stack = malloc(sizeof(SequentialStack));
    if (stack == NULL) {
        return NULL;
    }
    stack->top = 0;
    return stack;
}

bool sqstack_push(SequentialStack *stack, EleType value) {
    if (stack == NULL) {
        return false;
    }
    if (stack->top >= STACK_MAX_SIZE) {
        return false;
    }
    stack->data[stack->top++] = value;
    return true;
}

bool sqstack_pop(SequentialStack *stack) {
    if (stack == NULL) {
        return false;
    }
    if (sqstack_empty(stack)) {
        return false;
    }
    --stack->top;
    return true;
}

bool sqstack_clear(SequentialStack *stack) {
    if (stack == NULL) {
        return false;
    }
    stack->top = 0;
    return true;
}

EleType sqstack_top(SequentialStack *stack) {
    if (stack == NULL) {
        return 0;
    }
    if (sqstack_empty(stack)) {
        return 0;
    }
    return stack->data[stack->top - 1];
}

size_t sqstack_size(SequentialStack *stack) {
    if (stack == NULL) {
        return 0;
    }
    return stack->top;
}

bool sqstack_empty(SequentialStack *stack) {
    if (stack == NULL) {
        return true;
    }
    return stack->top == 0;
}

bool sqstack_full(SequentialStack *stack) {
    if (stack == NULL) {
        return false;
    }
    return stack->top == STACK_MAX_SIZE;
}
