/*
 * File: ArrayList.h
 * Author: Zhang Hai
 */

#ifndef _ARRAY_LIST_H_
#define _ARRAY_LIST_H_


#include "Common.h"


#define ARRAY_LIST_FOR_EACH(list, data) \
    for (data = list->array; data < list->array + list->size * list->elementSize; data += list->elementSize)


typedef struct {
    void **array;
    size_t elementSize;
    size_t size;
    size_t allocatedSize;
} ArrayList;


ArrayList *ArrayList_new(size_t elementSize);

void ArrayList_delete(ArrayList *list);

void *ArrayList_getAt(ArrayList *list, size_t index);

void ArrayList_addEnd(ArrayList *list, void *data);


#endif /* _ARRAY_LIST_H_ */
