/*
 * File: common.h
 * Author: Zhang Hai
 */

#ifndef _LMS_COMMON_H_
#define _LMS_COMMON_H_


#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#ifndef NULL
#define NULL 0
#endif

#ifndef BOOL
#define BOOL int
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE (!FALSE)
#endif

#define LMS_NEW(type) calloc(1, sizeof(type))

#define LMS_ALLOC(size) calloc(1, size);

#define LMS_MAX(var1, var2) ((var1) > (var2) ? (var1) : (var2))

#define LMS_MIN(var1, var2) ((var1) < (var2) ? (var1) : (var2))

#define LMS_SWAP(var1, var2, tmp) \
    do { \
        tmp = var1; \
        var1 = var2; \
        var2 = tmp; \
    } while (FALSE)

#define LMS_DECLARE_SERIALIZE_FUNCTION(name, type) \
    BOOL serialize_##name(type *value, FILE *file);

#define LMS_DECLARE_DESERIALIZE_FUNCTION(name, type) \
    BOOL deserialize_##name(type *value, FILE *file);


LMS_DECLARE_SERIALIZE_FUNCTION(size, size_t)

LMS_DECLARE_SERIALIZE_FUNCTION(int, int)

LMS_DECLARE_SERIALIZE_FUNCTION(bool, BOOL)

LMS_DECLARE_DESERIALIZE_FUNCTION(size, size_t)

LMS_DECLARE_DESERIALIZE_FUNCTION(int, int)

LMS_DECLARE_DESERIALIZE_FUNCTION(bool, BOOL)

BOOL serialize_string(char *value, FILE *file);

BOOL serialize_string_array(char *array[], size_t size, FILE *file);

BOOL deserialize_string(char **value, FILE *file);

BOOL deserialize_string_array(char *array[], size_t size, FILE *file);

void bool_print(BOOL bool);

char *string_clone(char *string);

BOOL string_contains(char *string, char *substring);

void string_array_clone(char *src[], char *dest[], size_t size);

void string_array_free(char *array[], size_t size);

BOOL string_array_is_equal(char *array1[], char *array2[],
        size_t size);

BOOL string_array_contains(char *array[], size_t size,
        char *substring);

void string_array_print(char *array[], size_t size);


#undef LMS_DECLARE_SERIALIZE_FUNCTION
#undef LMS_DECLARE_DESERIALIZE_FUNCTION


#endif /* _LMS_COMMON_H_ */
