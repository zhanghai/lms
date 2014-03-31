/*
 * File: Cli.c
 * Author: Zhang Hai
 */

#include "Lms.h"

#include "Library/Common.h"
#include "Library/ArrayList.h"
#include "Library/Console.h"


void print_book_filters() {

    // Using int for printf().
    int i;

    Console_printLine("Available book filters: ");

    Console_printLine("[%d] %s", 0, "Full Text");
    for (i = 1; i < BOOK_FILTERS_SIZE; ++i) {
        Console_printLine("[%d] %s", i, Book_FIELD_NAMES[i - 1]);
    }
}

BookList *filter_book(BookList *list) {

    string indexes[] = {"0", "1", "2", "3", "4", "5", "6", "7"};
    int index;
    string keyword;
    BookFilter filter;
    ArrayList filters = ArrayList_new(sizeof(BookFilter));
    BookList *result;

    print_book_filters();
    do {
        index = Console_readChoice("Enter filter index", indexes,
                sizeof(indexes));
        keyword = Console_readLine("Enter keyword: ");
        filter.filter = BOOK_FILTERS[index];
        filter.filterData = keyword;
    } while (true);

    filter.filter = BOOK_FILTERS[index];
    filter.filterData = keyword;
    result = BookList_search(list, filter);
    Memory_free(keyword);

    return result;
}

void search_book(BookList *list) {

    BookList *result;
    BookNode *node;

    print_book_filters();

    result = filter_book(list);

    BOOK_LIST_FOR_EACH(result, node) {
        Book_print(stdout, node->data);
    }

    BookList_delete(list);
}

void delete_book(BookList *list) {

    BookList *result;
    BookNode *node;

    print_book_filters();

    result = filter_book(list);

    BOOK_LIST_FOR_EACH(result, node) {
        Book_print(stdout, node->data);
        // TODO
        BookList_remove(list, node->data);
    }

    BookList_delete(list);
}
