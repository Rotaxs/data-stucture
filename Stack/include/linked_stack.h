#pragma once

#include <stdbool.h>
#include <stddef.h>

#ifndef STACK_ELEMENT_TYPE
#define STACK_ELEMENT_TYPE
typedef int EleType;
#endif

typedef struct LinkedStackNode {
    EleType data;
    struct LinkedStackNode *next;
} LinkedStackNode;

typedef struct {
    LinkedStackNode *top;
    size_t size;
} LinkedStack;

LinkedStack *ltstack_init(void);
bool ltstack_push(LinkedStack *stack, EleType value);
bool ltstack_pop(LinkedStack *stack);
bool ltstack_clear(LinkedStack *stack);
EleType ltstack_top(LinkedStack *stack);
size_t ltstack_size(LinkedStack *stack);
bool ltstack_empty(LinkedStack *stack);
bool ltstack_destroy(LinkedStack *stack);
