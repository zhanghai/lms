/**
 * @file Object.c
 * @author: Zhang Hai
 */

#include "Object.h"


void Object_initialize(Object *this) {
    _$(this, new) = Object_new;
    _$(this, delete) = Object_delete;
}

void Object_finalize(Object *this) {}

OBJECT_DEFINE_NEW(Object, Object_Fields, Object_Methods)

OBJECT_DEFINE_DELETE(Object)
