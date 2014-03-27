/*
 * File: operation.c
 * Author: Zhang Hai
 */

#include "operation.h"

#include <strings.h>


#define MATCH_OPERATION_TYPE(statement, type) \
    (strncasecmp(statement, OPERATION_##type##_STRING, sizeof(OPERATION_##type##_STRING)) == 0)

#define SET_OPERATION_TYPE(value, position, type) \
    do { \
        value = OPERATION_##type; \
        position += sizeof(OPERATION_##type##_STRING); \
    } while (FALSE)


static char OPERATION_SEARCH_STRING[] = "SEARCH";
static char OPERATION_INSERT_STRING[] = "INSERT";
static char OPERATION_MODIFY_STRING[] = "MODIFY";
static char OPERATION_DELETE_STRING[] = "DELETE";


static Operation *operation_new(OPERATION_TYPE type, void *criteria);


static Operation *operation_new(OPERATION_TYPE type, void *criteria) {

    Operation *operation = LMS_NEW(Operation);

    operation->type = type;
    operation->criteria = criteria;

    return operation;
}

Operation *operation_delete(Operation *operation) {

    // FIXME
    free(operation->criteria);

    return operation;
}

Operation *operation_parse(char *statement) {

    char *position = statement;
    OPERATION_TYPE type;
    void *criteria;

    if (MATCH_OPERATION_TYPE(position, SEARCH)) {
        SET_OPERATION_TYPE(type, position, SEARCH);
    } else if(MATCH_OPERATION_TYPE(position, INSERT)) {
        SET_OPERATION_TYPE(type, position, INSERT);
    } else if(MATCH_OPERATION_TYPE(position, MODIFY)) {
        SET_OPERATION_TYPE(type, position, MODIFY);
    } else if(MATCH_OPERATION_TYPE(position, DELETE)) {
        SET_OPERATION_TYPE(type, position, DELETE);
    }

    // TODO: Build criteria.
    criteria = NULL;
    return operation_new(type, criteria);
}


#undef MATCH_OPERATION_TYPE
#undef SET_OPERATION_TYPE
