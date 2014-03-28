/*
 * File: book_filter.h
 * Author: Zhang Hai
 */

#ifndef _BOOK_FILTER_H_
#define _BOOK_FILTER_H_


#include "common.h"

#include "book.h"


#define DECLARE_BOOK_FILTER(member) \
    BOOL book_filter_##member(Book *book, void *member);


DECLARE_BOOK_FILTER(title)

DECLARE_BOOK_FILTER(authors)

DECLARE_BOOK_FILTER(number)

DECLARE_BOOK_FILTER(subjects)

DECLARE_BOOK_FILTER(publisher)

DECLARE_BOOK_FILTER(year)

DECLARE_BOOK_FILTER(circulating)

BOOL book_filter_string(Book *book, void *string);


#undef DECLARE_BOOK_FILTER


#endif /* _BOOK_FILTER_H_ */
