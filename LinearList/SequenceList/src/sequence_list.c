#include "sequence_list.h"
#include <stdio.h>
#include <stdlib.h>

SequenceList *sqlist_make(void) {
    SequenceList *sqlist = (SequenceList *)malloc(sizeof(SequenceList));
    if (sqlist == NULL) {
        return NULL;
    }
    sqlist->len = 0;
    return sqlist;
}

int sqlist_length(SequenceList *sqlist) {
    return sqlist->len;
}

bool sqlist_insert(SequenceList *sqlist, int p, EleType x) {
    if (sqlist->len >= MAXLEN) {
        return false;
    }
    if (p < 0 || p > sqlist->len) {
        return false;
    }
    for (int i = sqlist->len - 1; i >= p; --i) {
        sqlist->v[i + 1] = sqlist->v[i];
    }
    ++sqlist->len;
    sqlist->v[p] = x;
    return true;
}

bool sqlist_delete(SequenceList *sqlist, int p) {
    if (p < 0 || p >= sqlist->len) {
        return false;
    }
    for (int i = p; i < sqlist->len - 1; ++i) {
        sqlist->v[i] = sqlist->v[i + 1];
    }
    --sqlist->len;
    return true;
}

bool sqlist_modify(SequenceList *sqlist, int p, EleType x) {
    if (p < 0 || p >= sqlist->len) {
        return false;
    }
    sqlist->v[p] = x;
    return true;
}

int sqlist_query(SequenceList *sqlist, EleType x) {
    for (int i = 0; i < sqlist->len; ++i) {
        if (sqlist->v[i] == x) {
            return i;
        }
    }
    return -1;
}

static void swap(EleType *a, EleType *b) {
    EleType c = *a;
    *a = *b;
    *b = c;
}

bool sqlist_flip(SequenceList *sqlist, int l, int r) {
    if (l < 0 || r >= sqlist->len || l > r) {
        return false;
    }
    for (; l < r; ++l, --r) {
        swap(&sqlist->v[l], &sqlist->v[r]);
    }
    return true;
}

bool sqlist_handswap(SequenceList *sqlist, int l, int m, int r) {
    if (l < 0 || r >= sqlist->len || l > m || m >= r) {
        return false;
    }
    sqlist_flip(sqlist, l, m);
    sqlist_flip(sqlist, m + 1, r);
    sqlist_flip(sqlist, l, r);
    return true;
}

void sqlist_free(SequenceList *sqlist) {
    free(sqlist);
}

void sqlist_print(SequenceList *sqlist) {
    for (int i = 0; i < sqlist->len; ++i) {
        printf("%d ", sqlist->v[i]);
    }
    printf("\n");
}