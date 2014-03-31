/*
 * File: Common.h
 * Author: Zhang Hai
 */

#ifndef _COMMON_H_
#define _COMMON_H_


#include <stdio.h>
#include <stdlib.h>

#include "primitives.h"
#include "bool.h"
#include "string.h"
#include "serialize.h"
#include "Application.h"
#include "Memory.h"


#define LMS_MAX(var1, var2) ((var1) > (var2) ? (var1) : (var2))

#define LMS_MIN(var1, var2) ((var1) < (var2) ? (var1) : (var2))

#define LMS_SWAP(var1, var2, tmp) \
    do { \
        tmp = var1; \
        var1 = var2; \
        var2 = tmp; \
    } while (false)


typedef int (*Comparator)(void *data1, void *data2);



#endif /* _COMMON_H_ */
