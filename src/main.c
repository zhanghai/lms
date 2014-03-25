/*
 * File: main.c
 * Author: Zhang Hai
 */

#include <stdio.h>
#include <stdlib.h>

#include "lms.h"

#define DATAFILE "lms.dat"

void test_serialize() {
    BookList *list = book_list_new();
    char *title = "title";
    char *authors[5] = {"author1", "author2", "author3", "", ""};
    char *number = "number123";
    char *subjects[5] = {"author1", "author2", "author3", "", ""};
    char *publisher = "publisher";
    char *year = "year";
    BOOL circulating = TRUE;
    Book *book = book_new(title, authors, number, subjects, publisher,
            year, circulating);
    FILE *file = fopen(DATAFILE, "wb");
    book_list_add_end(list, book);
    book_list_serialize(list, file);
    book_list_delete(list);
    fclose(file);
}

void test_deserialize() {
    BookList *list;
    FILE *file = fopen(DATAFILE, "rb");
    list = book_list_deserialize(file);
    book_print(list->head->book);
    book_list_delete(list);
    fclose(file);
}

int main(void) {
    test_serialize();
    test_deserialize();
    inputchoice();
    return 0;
}


int inputchoice(){

	int mychoice;

	printf("Enter your choice");
	printf("1 - add a new book.\n");
	printf("2 - modify a book.\n");
	printf("3 - delete a book.\n");
	printf("4 - search a book.\n");
	printf("5 - display a book");
}
