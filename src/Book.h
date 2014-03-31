/*
 * File: Book.h
 * Author: Zhang Hai
 */

#ifndef _BOOK_H_
#define _BOOK_H_


#include "Common.h"


typedef struct {
    size_t reference_count;
    char *title;
    char *authors[5];
    char *number;
    char *subjects[5];
    char *publisher;
    char *year;
    BOOL circulating;
} Book;


extern char* BOOK_FIELD_NAMES[];


Book *Book_new(char *title, char *authors[5], char *number,
        char *subjects[5], char *publisher, char *year,
        BOOL circulating);

void Book_addReference(Book *book);

void Book_removeReference(Book *book);

BOOL Book_serialize(Book *book, FILE *file);

Book *Book_deserialize(FILE *file);

Book *Book_clone(Book *book);

BOOL Book_isEqual(Book *book1, Book *book2);

void Book_print(Book *book);


#endif /* _BOOK_H_ */
