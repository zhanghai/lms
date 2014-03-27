/*
 * File: operation.h
 * Author: Zhang Hai
 */

#ifndef _OPERATION_H_
#define _OPERATION_H_


#include "common.h"


typedef enum {
    OPERATION_SEARCH,
    OPERATION_INSERT,
    OPERATION_MODIFY,
    OPERATION_DELETE
} OPERATION_TYPE;


typedef struct {
    OPERATION_TYPE type;
    void *criteria;
} Operation;


Operation *operation_parse(char *statement);


#endif /* _OPERATION_H_ */
