/*
 * File: Cli.c
 * Author: Zhang Hai
 */

#include "Lms.h"

#include "Library/ArrayList.h"
#include "Library/Console.h"


static void Lms_printBookFilters();

static void Lms_printBookNotFound();

static BookList *Lms_filterBook(BookList *list);


static void Lms_printBookFilters() {

    // Using int for printf().
    int i;

    Console_printLine("Available book filters: ");

    Console_printLine("[%d] %s", 0, "Full Text");
    for (i = 1; i < BOOK_FILTERS_SIZE; ++i) {
        Console_printLine("[%d] %s", i, Book_FIELD_NAMES[i - 1]);
    }
}

void Lms_printBookNotFound() {
    Console_printLine("No book found by specified filter(s).");
}

static BookList *Lms_filterBook(BookList *list) {

    string indexes[] = {"0", "1", "2", "3", "4", "5", "6", "7"};
    int index;
    string keyword;
    BookFilter *filter, compoundFilter;
    ArrayList *filters = ArrayList_new();
    BookList *result;

    Lms_printBookFilters();
    do {
        index = Console_readChoice("Enter filter index", indexes,
                sizeof(indexes) / sizeof(indexes[0]));
        keyword = Console_readLine("Enter keyword: ");
        filter = Memory_allocateType(BookFilter);
        filter->filter = BOOK_FILTERS[index];
        filter->filterData = keyword;
        ArrayList_addEnd(filters, filter);
    } while (Console_readYN("Add another filter?"));

    compoundFilter.filter = BookFilters_compound;
    compoundFilter.filterData = filters;
    result = BookList_search(list, compoundFilter);

    ARRAY_LIST_FOR_EACH(filters, filter) {
        Memory_free(filter->filterData);
        Memory_free(filter);
    }

    return result;
}

void Lms_searchBook(BookList *list) {

    BookList *result;
    BookNode *node;

    result = Lms_filterBook(list);

    if (result->size == 0) {
        Lms_printBookNotFound();
    } else {
        BOOK_LIST_FOR_EACH(result, node) {
            Book_print(stdout, node->data);
        }
    }

    BookList_delete(list);
}

void Lms_deleteBook(BookList *list) {

    BookList *result;
    BookNode *node;

    Lms_printBookFilters();

    result = Lms_filterBook(list);

    if (result->size == 0) {
        Lms_printBookNotFound();
    } else {
        BOOK_LIST_FOR_EACH(result, node) {
            Book_print(stdout, node->data);
            if (Console_readYN("Are you sure to delete this book?")) {
                BookList_remove(list, node->data);
            }
        }
    }

    BookList_delete(list);
}
