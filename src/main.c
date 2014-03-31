/*
 * File: main.c
 * Author: Zhang Hai
 */

#include "Lms.h"


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
    Lms_searchBook(list);
    BookList_delete(list);
    fclose(file);
}

int main(void) {
    test_serialize();
    test_deserialize();
    return 0;
}
