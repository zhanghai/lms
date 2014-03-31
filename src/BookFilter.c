/*
 * File: BookFilter.c
 * Author: Zhang Hai
 */

#include "BookFilter.h"

#include <strings.h>


#define DEFINE_BOOK_FILTER_STRING(member) \
    BOOL BookFilters_##member(Book *book, void *member) { \
        return string_contains(book->member, member); \
    }

#define DEFINE_BOOK_FILTER_STRING_ARRAY(member, size) \
    BOOL BookFilters_##member(Book *book, void *member) { \
        return string_array_contains(book->member, size, member); \
    }

#define DEFINE_BOOK_FILTER_BOOL(member) \
    BOOL BookFilters_##member(Book *book, void *member) { \
        return bool_is_equal(book->member, member); \
    }


BookFilter BOOK_FILTERS[] = {
    BookFilters_string,
    BookFilters_title,
    BookFilters_authors,
    BookFilters_number,
    BookFilters_publisher,
    BookFilters_subjects,
    BookFilters_year,
    BookFilters_circulating,
};

size_t BOOK_FILTERS_SIZE = 8;


DEFINE_BOOK_FILTER_STRING(title)

DEFINE_BOOK_FILTER_STRING_ARRAY(authors, 5)

DEFINE_BOOK_FILTER_STRING(number)

DEFINE_BOOK_FILTER_STRING_ARRAY(subjects, 5)

DEFINE_BOOK_FILTER_STRING(publisher)

DEFINE_BOOK_FILTER_STRING(year)

DEFINE_BOOK_FILTER_BOOL(circulating)

BOOL BookFilters_string(Book *book, void *string) {
    return BookFilters_title(book, string)
            || BookFilters_authors(book, string)
            || BookFilters_number(book, string)
            || BookFilters_subjects(book, string)
            || BookFilters_publisher(book, string)
            || BookFilters_year(book, string);
}


#undef DEFINE_BOOK_FILTER_STRING
#undef DEFINE_BOOK_FILTER_STRING_ARRAY
#undef DEFINE_BOOK_FILTER_BOOL
