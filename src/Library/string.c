/**
 * @file string.c
 * @author Zhang Hai
 */

#include "string.h"

#ifdef __gnu_linux__
#define __USE_GNU_STRCASESTR__
#endif

// For toupper() and tolower()
#include <ctype.h>
#ifdef __USE_GNU_STRCASESTR__
#define __USE_GNU
#endif
#include <string.h>
#ifdef __USE_GNU_STRCASESTR__
#undef __USE_GNU
#endif
#include <strings.h>

#include "array.h"
#include "Memory.h"


string string_EMPTY = "";


string string_clone(string theString) {
    string clone = Memory_allocate((string_length(theString) + 1) * sizeof(char));
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

bool string_contains(string theString, string subString) {
    return strstr(theString, subString) != null;
}

#ifdef __USE_GNU_STRCASESTR__
bool string_containsIgnoreCase(string theString, string subString) {
    return strcasestr(theString, subString) != null;
}
#else
bool string_containsIgnoreCase(string theString, string subString) {
    string *stringUpper = string_toUpper(string_clone(theString)),
            subStringUpper = string_toUpper(string_clone(subString));
    bool result = strstr(stringUpper, subStringUpper);
    Memory_free(stringUpper);
    Memory_free(subStringUpper);
    return result;
}
#endif

size_t string_length(string theString) {
    return strlen(theString);
}

bool string_isEmpty(string theString) {
    return string_length(theString) == 0;
}

void string_toUpper(string theString) {
    size_t i, size;
    size = string_length(theString);
    for (i = 0; i < size; ++i) {
        // No conversion will be done if not possible.
        theString[i] = toupper(theString[i]);
    }
}

void string_toLower(string theString) {
    size_t i, size;
    size = string_length(theString);
    for (i = 0; i < size; ++i) {
        // No conversion will be done if not possible.
        theString[i] = tolower(theString[i]);
    }
}

/**
 * Append a string to an existing string.
 * @param theString The existing string.
 * @param extra The extra string to be appended.
 * @return The address of the string appended by extra, may differ
 *         from the original string.
 */
string string_append(string theString, string extra) {
    size_t oldLength = string_length(theString);
    theString = Memory_reallocate(theString,
            oldLength + string_length(extra) + 1);
    strcpy(theString + oldLength, extra);
    return theString;
}

/**
 * Concatenate a string with another string.
 * @param theString The first string.
 * @param extra The second string.
 * @return The new concatenated string.
 */
string string_concatenate(string first, string second) {
    size_t firstLength = string_length(first);
    string concatenated = Memory_allocate(firstLength + string_length(second) + 1);
    strcpy(concatenated + firstLength, second);
    return concatenated;
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

void string_array_copy(string source[], string destination[],
        size_t size) {
    array_copy(source, destination, size, sizeof(string));
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

bool string_array_isEqualIgnoreCase(string array1[], string array2[],
        size_t size) {
    size_t i;
    for (i = 0; i < size; ++i) {
        if (!string_isEqualIgnoreCase(array1[i], array2[i])) {
            return false;
        }
    }
    return true;
}

size_t string_array_containsEqual(string array[], size_t size,
        string theString) {
    size_t i;
    for (i = 0; i < size; ++i) {
        if (string_isEqual(array[i], theString)) {
            return i;
        }
    }
    return -1;
}

size_t string_array_containsEqualIgnoreCase(string array[],
        size_t size, string theString) {
    size_t i;
    for (i = 0; i < size; ++i) {
        if (string_isEqualIgnoreCase(array[i], theString)) {
            return i;
        }
    }
    return -1;
}

bool string_array_contains(string array[], size_t size,
        string subString) {
    size_t i;
    for (i = 0; i < size; ++i) {
        if (string_contains(array[i], subString)) {
            return true;
        }
    }
    return false;
}

bool string_array_containsIgnoreCase(string array[], size_t size,
        string subString) {
    size_t i;
    for (i = 0; i < size; ++i) {
        if (string_containsIgnoreCase(array[i], subString)) {
            return true;
        }
    }
    return false;
}

void string_array_print(string array[], size_t size, string splitter,
        FILE *file) {
    int i;
    for (i = 0; i < size; ++i) {
        if (i != 0) {
            fprintf(file, splitter);
        }
        fprintf(file, array[i]);
    }
}

void string_array_printSkipEmpty(string array[], size_t size,
        string splitter, FILE *file) {
    int i;
    for (i = 0; i < size; ++i) {
        if (string_isEmpty(array[i])) {
            continue;
        }
        if (i != 0) {
            fprintf(file, splitter);
        }
        fprintf(file, array[i]);
    }
}
