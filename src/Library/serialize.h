/*
 * File: serialize.h
 * Author: Zhang Hai
 */

#ifndef _SERIALIZE_H_
#define _SERIALIZE_H_


#include <stdio.h>

#include "primitives.h"


#define LMS_DECLARE_SERIALIZE_FUNCTION(type) \
    bool type##_serialize(type *value, FILE *file);

#define LMS_DECLARE_DESERIALIZE_FUNCTION(type) \
    bool type##_deserialize(type *valueString, FILE *file);


LMS_DECLARE_SERIALIZE_FUNCTION(size_t)

LMS_DECLARE_DESERIALIZE_FUNCTION(size_t)

LMS_DECLARE_SERIALIZE_FUNCTION(bool)

LMS_DECLARE_DESERIALIZE_FUNCTION(bool)

bool string_serialize(string theString, FILE *file);

bool string_deserialize(string *theString, FILE *file);

bool string_array_serialize(string array[], size_t size, FILE *file);

bool string_array_deserialize(string array[], size_t size,
        FILE *file);


#undef LMS_DECLARE_SERIALIZE_FUNCTION
#undef LMS_DECLARE_DESERIALIZE_FUNCTION


#endif /* _SERIALIZE_H_ */
