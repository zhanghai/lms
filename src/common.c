/*
 * File: common.c
 * Author: Zhang Hai
 */

#include "common.h"

#include <string.h>


LMS_DEFINE_SERIALIZE_FUNCTION(size, size_t)

LMS_DEFINE_SERIALIZE_FUNCTION(int, int)

LMS_DEFINE_SERIALIZE_FUNCTION(bool, BOOL)

LMS_DEFINE_DESERIALIZE_FUNCTION(size, size_t)

LMS_DEFINE_DESERIALIZE_FUNCTION(int, int)

LMS_DEFINE_DESERIALIZE_FUNCTION(bool, BOOL)

BOOL serialize_string(char *value, FILE *file) {
    size_t size = strlen(value) + 1;
    return serialize_size(&size, file)
            && fwrite(value, size, 1, file) == 1;
}

BOOL serialize_string_array(char *array[], size_t size, FILE *file) {
    size_t i;
    for (i = 0; i < size; ++i) {
        if (!serialize_string(array[i], file)) {
            return FALSE;
        }
    }
    return TRUE;
}

/**
 * Deserialize a string from file.
 * Note that the memory will be allocated for string.
 * @param value Pointer to the string.
 * @param file The file to deserialize string from.
 * @return Whether the deserialization is successful.
 */
BOOL deserialize_string(char **value, FILE *file) {
    size_t size;
    if (!deserialize_size(&size, file)) {
        return FALSE;
    }
    *value = LMS_ALLOC(size);
    return fread(*value, size, 1, file) == 1;
};

BOOL deserialize_string_array(char *array[], size_t size,
        FILE *file) {
    size_t i;
    for (i = 0; i < size; ++i) {
        if (!deserialize_string(&array[i], file)) {
            return FALSE;
        }
    }
    return TRUE;
}

void bool_print(BOOL bool) {
    printf(bool ? "True" : "False");
}

char *string_clone(char *string) {
    char *clone = LMS_ALLOC(strlen(string) + 1);
    strcpy(clone, string);
    return clone;
}

/**
 * Make a deep copy of a string array.
 * @param src The source string array.
 * @param dest The destination string array.
 * @param size Size of both string arrays.
 */
void string_array_clone(char *src[], char *dest[], size_t size) {
    size_t i;
    for (i = 0; i < size; ++i) {
        dest[i] = string_clone(src[i]);
    }
}

void string_array_free(char *array[], size_t size) {
    size_t i;
    for (i = 0; i < size; ++i) {
        free(array[i]);
    }
}

void string_array_print(char *array[], size_t size) {
    int i;
    for (i = 0; i < size; ++i) {
        if (strlen(array[i]) == 0) {
            break;
        }
        if (i != 0) {
            printf("; ");
        }
        printf("%s", array[i]);
    }
}
