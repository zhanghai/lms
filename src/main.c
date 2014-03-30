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
	int choice;

    test_serialize();
    while((choice=input_choice())!=0){
    	switch(choice){
    	case 1: add_new_book(); break;
    	case 2: modify_book(); break:
    	case 3: delete_book(); break;
    	case 4: search_book(); break;
    	case 5: display_book(); break;
    	}
    }
    test_deserialize();
    return 0;
}


int input_choice(){

    int mychoice;

    printf("Enter your choice");
    printf("1 - add a new book.\n");
    printf("2 - modify a book.\n");
    printf("3 - delete a book.\n");
    printf("4 - search a book.\n");
    printf("5 - display a book");
    printf("0 - exit");
    scanf("%d", &mychoice);

    return mychoice;
}

void add_new_book(){
	char *title;
	char *authors[5];
	char *number;
	char *subjects[5];
	char *publisher;
	char *year;
	BOOL circulating;
	book_new(title, authors[5], number, subjects[5], publisher, year, BOOL circulating);
}

void modify_book(){
}

void delete_book(){
}

void search_book(){

}

void display_book(){
}
