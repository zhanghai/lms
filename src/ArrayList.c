/*
 * File: ArrayList.c
 * Author: Zhang Hai
 */

#include "ArrayList.h"


static const size_t INITIAL_ALLOCATION_SIZE = 8;


ArrayList *ArrayList_new() {

    ArrayList *list = LMS_NEW(ArrayList);

    list->array = LMS_ALLOC(INITIAL_ALLOCATION_SIZE * sizeof(void *));
    list->size = 0;
    list->allocatedSize = INITIAL_ALLOCATION_SIZE;

    return list;
}

void ArrayList_delete(ArrayList *list) {

    free(list->array);

    free(list);
}

void *ArrayList_getAt(ArrayList *list, size_t index) {

    if (index >= list->size) {
        return NULL;
    }

    return list->array[index];
}

void ArrayList_addEnd(ArrayList *list, void *data) {

    if (list->size == list->allocatedSize) {
        list->array = LMS_REALLOC(list->array,
                2 * list->allocatedSize * sizeof(void *));
        list->allocatedSize *= 2;
    }

    list->array[list->size] = data;
    ++list->size;
}
