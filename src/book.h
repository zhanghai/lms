/*
 * File: book.h
 * Author: Zhang Hai
 */

#ifndef _LMS_BOOK_H_
#define _LMS_BOOK_H_


#include "common.h"


typedef struct {
    char *title;
    char *authors[5];
    char *number;
    char *subjects[5];
    char *publisher;
    char *year;
    BOOL circulating;
} Book;


Book *book_new(char *title, char *authors[5], char *number,
        char *subjects[5], char *publisher, char *year,
        BOOL circulating);

void book_delete(Book *book);

BOOL book_serialize(Book *book, FILE *file);

Book *book_deserialize(FILE *file);

Book *book_clone(Book *book);

BOOL *book_is_equal(Book *book1, Book *book2);

void book_print(Book *book);


#endif /* _LMS_BOOK_H_ */
