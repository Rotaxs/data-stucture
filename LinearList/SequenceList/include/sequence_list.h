#pragma once

#include <stdbool.h>

#define MAXLEN 1000

typedef int EleType;

typedef struct SequenceList {
    EleType v[MAXLEN];
    int len;
} SequenceList;

SequenceList *sqlist_make(void);
int sqlist_length(SequenceList *);
bool sqlist_insert(SequenceList *, int, EleType);
bool sqlist_delete(SequenceList *, int);
bool sqlist_modify(SequenceList *, int, EleType);
int sqlist_query(SequenceList *, EleType);
bool sqlist_flip(SequenceList *, int, int);
bool sqlist_handswap(SequenceList *, int, int, int);
void sqlist_free(SequenceList *);
void sqlist_print(SequenceList *);
