/*
 * File: array_list.h
 * Author: Zhang Hai
 */

#ifndef _ARRAY_LIST_H_
#define _ARRAY_LIST_H_


#include "common.h"


#define ARRAY_LIST_FOR_EACH(list, index) \
    for (index = 0; index < list->size; ++index)


typedef struct {
    void *array[];
    size_t size;
    size_t allocated_size;
} ArrayList;


ArrayList *array_list_new();

void array_list_delete(ArrayList *list);

void *array_list_get_at(ArrayList *list, size_t index);

void array_list_add_end(ArrayList *list, void *data);


#endif /* _ARRAY_LIST_H_ */
