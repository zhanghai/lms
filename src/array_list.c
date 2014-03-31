/*
 * File: array_list.c
 * Author: Zhang Hai
 */

#include "array_list.h"


static const size_t INITIAL_ALLOCATION_SIZE = 8;


ArrayList *array_list_new() {

    ArrayList *list = LMS_NEW(ArrayList);

    list->array = LMS_ALLOC(INITIAL_ALLOCATION_SIZE * sizeof(void *));
    list->size = 0;
    list->allocated_size = INITIAL_ALLOCATION_SIZE;

    return list;
}

void array_list_delete(ArrayList *list) {

    free(list->array);

    free(list);
}

void *array_list_get_at(ArrayList *list, size_t index) {

    if (index >= list->size) {
        return NULL;
    }

    return list->array[index];
}

void array_list_add_end(ArrayList *list, void *data) {

    if (list->size == list->allocated_size) {
        list->array = LMS_REALLOC(list->array,
                2 * list->allocated_size * sizeof(void *));
        list->allocated_size *= 2;
    }

    list->array[list->size] = data;
    ++list->size;
}
