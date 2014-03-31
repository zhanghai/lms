/*
 * File: cli.c
 * Author: Zhang Hai
 */


#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "lms.h"


void print_book_filters() {

    // Using int for printf().
    int i;

    printf("Available book filters: ");

    printf("[%d] %s", 0, "Full Text");
    for (i = 1; i < BOOK_FILTERS_SIZE; ++i) {
        printf("[%d] %s", i, BOOK_FIELD_NAMES[i - 1]);
    }
}

BookList *filter_book(BookList *list) {

    char *input;
    // Using int for sscanf().
    int index;
    BookFilter filter;
    BookList *result;

    print_book_filters();
    while (TRUE) {
        input = readline("Enter filter index: ");
        if (input == NULL) {
            return NULL;
        }
        if (sscanf(input, "%d", &index) != 1
                || index < 0 || index >= BOOK_FILTERS_SIZE) {
            printf("Invalid input \"%s\", please try again.\n", input);
            free(input);
            continue;
        }
        free(input);
        filter = BOOK_FILTERS[index];
        break;
    }

    input = readline("Enter keyword: ");
    if (input == NULL) {
        return NULL;
    }
    if (strlen(input) > 0) {
        add_history(input);
    }
    result = BookList_search(list, filter, input);
    free(input);

    return result;
}

void search_book(BookList *list) {

    BookList *result;
    BookNode *node;

    print_book_filters();

    result = filter_book(list);

    BOOK_LIST_FOR_EACH(result, node) {
        Book_print(node->book);
    }

    BookList_delete(list);
}

void delete_book(BookList *list) {

    BookList *result;
    BookNode *node;

    print_book_filters();

    result = filter_book(list);

    BOOK_LIST_FOR_EACH(result, node) {
        Book_print(node->book);
        // TODO
        BookList_remove(list, node->book);
    }

    BookList_delete(list);
}
