/*
 * File: Common.c
 * Author: Zhang Hai
 */

#include "Common.h"

#include <string.h>


#define LMS_DEFINE_SERIALIZE_FUNCTION(name, type) \
    BOOL serialize_##name(type *value, FILE *file) { \
        return fwrite(value, sizeof(type), 1, file) == 1; \
    };

#define LMS_DEFINE_DESERIALIZE_FUNCTION(name, type) \
    BOOL deserialize_##name(type *value, FILE *file) { \
        return fread(value, sizeof(type), 1, file) == 1; \
    };


static char *BOOL_TRUE_STRING = "True";

static char *BOOL_FALSE_STRING = "False";


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

BOOL bool_is_equal(BOOL bool, char *string) {
    return bool ? strcasecmp(BOOL_TRUE_STRING, string)
            : strcasecmp(BOOL_FALSE_STRING, string);
}

void bool_print(BOOL bool) {
    printf(bool ? BOOL_TRUE_STRING : BOOL_FALSE_STRING);
}

char *string_clone(char *string) {
    char *clone = LMS_ALLOC(strlen(string) + 1);
    strcpy(clone, string);
    return clone;
}

BOOL string_contains(char *string, char *substring) {
    return strstr(string, substring) != NULL;
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

BOOL string_array_is_equal(char *array1[], char *array2[],
        size_t size) {
    size_t i;
    for (i = 0; i < size; ++i) {
        if (strcmp(array1[i], array2[i]) != 0) {
            return FALSE;
        }
    }
    return TRUE;
}

BOOL string_array_contains(char *array[], size_t size,
        char *substring) {
    size_t i;
    for (i = 0; i < size; ++i) {
        if (string_contains(array[i], substring)) {
            return TRUE;
        }
    }
    return FALSE;
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


#undef LMS_DEFINE_SERIALIZE_FUNCTION
#undef LMS_DEFINE_DESERIALIZE_FUNCTION
