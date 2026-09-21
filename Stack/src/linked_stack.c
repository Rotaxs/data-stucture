#include "linked_stack.h"
#include <stdlib.h>

LinkedStack *ltstack_init(void) {
    LinkedStack *stack = malloc(sizeof(LinkedStack));
    if (stack == NULL) {
        return NULL;
    }
    stack->size = 0;
    stack->top = NULL;
    return stack;
}

bool ltstack_push(LinkedStack *stack, EleType value) {
    if (stack == NULL) {
        return false;
    }
    LinkedStackNode *node = malloc(sizeof(LinkedStackNode));
    if (node == NULL) {
        return false;
    }
    ++stack->size;
    node->data = value;
    node->next = stack->top;
    stack->top = node;
    return true;
}

bool ltstack_pop(LinkedStack *stack) {
    if (stack == NULL) {
        return false;
    }
    if (stack->size == 0) {
        return false;
    }
    LinkedStackNode *top = stack->top;
    stack->top = stack->top->next;
    free(top);
    --stack->size;
    return true;
}

bool ltstack_clear(LinkedStack *stack) {
    if (stack == NULL) {
        return false;
    }
    while (stack->top) {
        LinkedStackNode *node = stack->top;
        stack->top = node->next;
        free(node);
    }
    stack->size = 0;
    // stack->top = NULL;
    return true;
}

EleType ltstack_top(LinkedStack *stack) {
    if (stack == NULL) {
        return 0;
    }
    if (stack->size == 0) {
        return 0;
    }
    return stack->top->data;
}

size_t ltstack_size(LinkedStack *stack) {
    if (stack == NULL) {
        return 0;
    }
    return stack->size;
}

bool ltstack_empty(LinkedStack *stack) {
    if (stack == NULL) {
        return true;
    }
    return stack->size == 0;
}

bool ltstack_destroy(LinkedStack *stack) {
    if (stack == NULL) {
        return false;
    }
    ltstack_clear(stack);
    free(stack);
    return true;
}
