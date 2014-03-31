/*
 * File: BookFilter.h
 * Author: Zhang Hai
 */

#ifndef _BOOK_FILTER_H_
#define _BOOK_FILTER_H_


#include "Library/Common.h"

#include "Book.h"


#define DECLARE_BOOK_FILTER(member) \
    bool BookFilters_##member(Book *book, void *member);


typedef bool (*BookFilter)(Book *book, void *criteria);


extern BookFilter BOOK_FILTERS[];

extern size_t BOOK_FILTERS_SIZE;


DECLARE_BOOK_FILTER(title)

DECLARE_BOOK_FILTER(authors)

DECLARE_BOOK_FILTER(number)

DECLARE_BOOK_FILTER(subjects)

DECLARE_BOOK_FILTER(publisher)

DECLARE_BOOK_FILTER(year)

DECLARE_BOOK_FILTER(circulating)

bool BookFilters_string(Book *book, void *string);


#undef DECLARE_BOOK_FILTER


#endif /* _BOOK_FILTER_H_ */
