/*
 * File: string.c
 * Author: Zhang Hai
 */

#include "string.h"

#include <string.h>
#include <strings.h>

#include "Memory.h"


string string_clone(string theString) {
    string clone = Memory_allocate(string_length(theString) + 1);
    strcpy(clone, theString);
    return clone;
}

bool string_isEqual(string string1, string string2) {
    return string_compare(string1, string2) == 0;
}

int string_isEqualIgnoreCase(string string1, string string2) {
    return string_compareIgnoreCase(string1, string2) == 0;
}

int string_compare(string string1, string string2) {
    return strcmp(string1, string2);
}

int string_compareIgnoreCase(string string1, string string2) {
    return strcasecmp(string1, string2);
}

bool string_contains(string theString, string substring) {
    return strstr(theString, substring) != null;
}

size_t string_length(string theString) {
    return strlen(theString);
}

/**
 * Make a deep copy of a string array.
 * @param source The source string array.
 * @param destination The destination string array.
 * @param size Size of both string arrays.
 */
void string_array_clone(string src[], string dest[], size_t size) {
    size_t i;
    for (i = 0; i < size; ++i) {
        dest[i] = string_clone(src[i]);
    }
}

void string_array_free(string array[], size_t size) {
    size_t i;
    for (i = 0; i < size; ++i) {
        Memory_free(array[i]);
    }
}

bool string_array_isEqual(string array1[], string array2[],
        size_t size) {
    size_t i;
    for (i = 0; i < size; ++i) {
        if (!string_isEqual(array1[i], array2[i])) {
            return false;
        }
    }
    return true;
}

bool string_array_contains(string array[], size_t size,
        string substring) {
    size_t i;
    for (i = 0; i < size; ++i) {
        if (string_contains(array[i], substring)) {
            return true;
        }
    }
    return false;
}

void string_array_print(FILE *file, string array[], size_t size) {
    int i;
    for (i = 0; i < size; ++i) {
        if (string_length(array[i]) == 0) {
            break;
        }
        if (i != 0) {
            fprintf(file, "; ");
        }
        fprintf(file, "%s", array[i]);
    }
}
