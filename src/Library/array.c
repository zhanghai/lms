/*
 * File: array.c
 * Author: Zhang Hai
 */

#include "array.h"

#include <string.h>


void array_copy(void *source, void *destination, size_t size,
        size_t elementSize) {
    memcpy(destination, source, size * elementSize);
}
