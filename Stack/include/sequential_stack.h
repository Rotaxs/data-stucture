#pragma once

#include <stdbool.h>
#include <stddef.h>

#ifndef STACK_ELEMENT_TYPE
#define STACK_ELEMENT_TYPE
typedef int EleType;
#endif

#define STACK_MAX_SIZE 1000

typedef struct {
    EleType data[STACK_MAX_SIZE];
    int top;
} SequentialStack;

SequentialStack *sqstack_init(void);
bool sqstack_push(SequentialStack *stack, EleType value);
bool sqstack_pop(SequentialStack *stack);
bool sqstack_clear(SequentialStack *stack);
EleType sqstack_top(SequentialStack *stack);
size_t sqstack_size(SequentialStack *stack);
bool sqstack_empty(SequentialStack *stack);
bool sqstack_full(SequentialStack *stack);
