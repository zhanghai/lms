/*
 * File: main.c
 * Author: Zhang Hai
 */

#include <stdio.h>
#include <stdlib.h>

#include "lms.h"

#define DATAFILE "lms.dat"

void test_serialize() {
    BookList *list = BookList_new();
    string title = "title";
    string authors[5] = {"author1", "author2", "author3", "", ""};
    string number = "number123";
    string subjects[5] = {"author1", "author2", "author3", "", ""};
    string publisher = "publisher";
    string year = "year";
    bool circulating = true;
    Book *book = Book_new(title, authors, number, subjects, publisher,
            year, circulating);
    FILE *file = fopen(DATAFILE, "wb");
    BookList_addEnd(list, book);
    BookList_serialize(list, file);
    BookList_delete(list);
    fclose(file);
}

void test_deserialize() {
    BookList *list;
    FILE *file = fopen(DATAFILE, "rb");
    list = BookList_deserialize(file);
    Book_print(stdin, list->head->data);
    BookList_delete(list);
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

    return 0;
}
