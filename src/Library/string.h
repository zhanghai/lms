/*
 * File: string.h
 * Author: Zhang Hai
 */

#ifndef _STRING_H_
#define _STRING_H_


#include "primitives.h"

#include "stdio.h"


string string_clone(string theString);

bool string_isEqual(string string1, string string2);

bool string_isEqualIgnoreCase(string string1, string string2);

int string_compare(string string1, string string2);

int string_compareIgnoreCase(string string1, string string2);

bool string_contains(string theString, string substring);

size_t string_length(string theString);

void string_array_clone(string source[], string destination[],
        size_t size);

void string_array_free(string array[], size_t size);

bool string_array_isEqual(string array1[], string array2[],
        size_t size);

size_t string_array_containsEqual(string array[], size_t size,
        string theString);

bool string_array_contains(string array[], size_t size,
        string substring);

void string_array_print(FILE* file, string array[], size_t size,
        string splitter);


#endif /* _STRING_H_ */
