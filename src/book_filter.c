/*
 * File: book_filter.c
 * Author: Zhang Hai
 */

#include "book_filter.h"

#include <strings.h>


#define DEFINE_BOOK_FILTER_STRING(member) \
    BOOL book_filter_##member(Book *book, void *member) { \
        return string_contains(book->member, member); \
    }

#define DEFINE_BOOK_FILTER_STRING_ARRAY(member, size) \
    BOOL book_filter_##member(Book *book, void *member) { \
        return string_array_contains(book->member, size, member); \
    }

#define DEFINE_BOOK_FILTER_BOOL(member) \
    BOOL book_filter_##member(Book *book, void *member) { \
        return book->member == *(BOOL *)member; \
    }


DEFINE_BOOK_FILTER_STRING(title)

DEFINE_BOOK_FILTER_STRING_ARRAY(authors, 5)

DEFINE_BOOK_FILTER_STRING(number)

DEFINE_BOOK_FILTER_STRING_ARRAY(subjects, 5)

DEFINE_BOOK_FILTER_STRING(publisher)

DEFINE_BOOK_FILTER_STRING(year)

DEFINE_BOOK_FILTER_BOOL(circulating)

BOOL book_filter_string(Book *book, void *string) {
    return book_filter_title(book, string)
            || book_filter_authors(book, string)
            || book_filter_number(book, string)
            || book_filter_subjects(book, string)
            || book_filter_publisher(book, string)
            || book_filter_year(book, string);
}


#undef DEFINE_BOOK_FILTER_STRING
#undef DEFINE_BOOK_FILTER_STRING_ARRAY
#undef DEFINE_BOOK_FILTER_BOOL
