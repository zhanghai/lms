/*
 * File: Book.h
 * Author: Zhang Hai
 */

#ifndef _BOOK_H_
#define _BOOK_H_


#include "Library/Common.h"


typedef struct {
    size_t reference_count;
    string title;
    string authors[5];
    string number;
    string subjects[5];
    string publisher;
    string year;
    bool circulating;
} Book;


typedef int (*BookComparator)(Book *book1, Book *book2);

typedef bool (*BookFilterFunction)(Book *book, void *filterData);

typedef struct {
    BookFilterFunction filter;
    void *filterData;
} BookFilter;


extern string Book_FIELD_NAMES[];


Book *Book_new(string title, string authors[5], string number,
        string subjects[5], string publisher, string year,
        bool circulating);

void Book_addReference(Book *book);

void Book_removeReference(Book *book);

bool Book_serialize(Book *book, FILE *file);

Book *Book_deserialize(FILE *file);

Book *Book_clone(Book *book);

bool Book_isEqual(Book *book1, Book *book2);

void Book_print(Book *book, FILE *file);


#endif /* _BOOK_H_ */
