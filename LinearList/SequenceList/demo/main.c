#include "sequence_list.h"
#include <stdio.h>

int main() {
    SequenceList *sqlist = sqlist_make();
    if (sqlist == NULL) {
        return 1;
    }

    sqlist_insert(sqlist, 0, 1);
    sqlist_insert(sqlist, 1, 2);
    sqlist_insert(sqlist, 2, 3);

    sqlist_print(sqlist);

    sqlist_insert(sqlist, 1, 100);
    sqlist_print(sqlist);

    sqlist_insert(sqlist, 4, 400);
    sqlist_print(sqlist);

    sqlist_delete(sqlist, 1);
    sqlist_print(sqlist);

    sqlist_modify(sqlist, 1, 200);
    sqlist_print(sqlist);

    printf("%d\n", sqlist_query(sqlist, 3));

    sqlist_flip(sqlist, 0, 3);
    sqlist_print(sqlist);

    sqlist_free(sqlist);

    return 0;
}