/*
 * File: bool.c
 * Author: Zhang Hai
 */

#include "bool.h"
#include "string.h"


static const string BOOL_FALSE_STRING = "False";
static const string BOOL_TRUE_STRING = "True";


bool bool_is_equal(bool theBool, string theString) {
    return theBool ?
            string_isEqualIgnoreCase(BOOL_TRUE_STRING, theString)
            : string_isEqualIgnoreCase(BOOL_FALSE_STRING, theString);
}

void bool_print(FILE *file, bool theBool) {
    fprintf(file, theBool ? BOOL_TRUE_STRING : BOOL_FALSE_STRING);
}
