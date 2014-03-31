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
	char *authors[5] = { "author1", "author2", "author3", "", "" };
	char *number = "number123";
	char *subjects[5] = { "author1", "author2", "author3", "", "" };
	char *publisher = "publisher";
	char *year = "year";
	BOOL circulating = TRUE;
	Book *book = book_new(title, authors, number, subjects, publisher, year,
			circulating);
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

int input_choice();
BookList *get_booklist(BookList *list);
void add_new_book(BookList *list);
void delete_book(BookList* list);
void modify_book(BookList *list);
void search_book(BookList *list);

int main(void) {
	int choice;
	BookList *list;


	while ((choice = input_choice()) != 0) {
		switch (choice) {
		case 1:
			add_new_book(list);
			break;
		case 2:
			modify_book(list);
			break;
		case 3:
			delete_book(list);
			break;
		case 4:
			search_book(list);
			break;
		}
	}
	return 0;
}

int input_choice() {

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

void add_new_book(BookList *list) {
	Book *book;
	char *title;
	char *authors[5];
	char *number;
	char *subjects[5];
	char *publisher;
	char *year;
	BOOL circulating;
	char input[80];
	printf("the title:");
	scanf("%80s", input);
	title = input;
	printf("the first author:");
	scanf("%80s", input);
	authors[0] = input;
	printf("the second author:");
	scanf("%80s", input);
	authors[1] = input;
	printf("the third author:");
	scanf("%80s", input);
	authors[2] = input;
	printf("the fourth author:");
	scanf("%80s", input);
	authors[3] = input;
	printf("the fifth author:");
	scanf("%80s", input);
	authors[4] = input;
	printf("the number:");
	scanf("%80s", input);
	number = input;
	printf("the first subject:");
	scanf("%80s", input);
	authors[0] = input;
	printf("the second subject:");
	scanf("%80s", input);
	subjects[1] = input;
	printf("the third subject:");
	scanf("%80s", input);
	subjects[2] = input;
	printf("the fourth subject:");
	scanf("%80s", input);
	subjects[3] = input;
	printf("the fifth subject:");
	scanf("%80s", input);
	subjects[4] = input;
	printf("the publisher:");
	scanf("%80s", input);
	publisher = input;
	printf("the year:");
	scanf("%80s", input);
	year = input;
	printf("the circulating");
	scanf("%d", &circulating);

	book = book_new(title, authors, number, subjects, publisher, year, circulating);
	book_list_add_end(list, book);
	book_remove_reference(book);
}

void modify_book(BookList *list) {
	BookList *small = get_booklist(list);
	BookNode *node;
	char input[80];
	int i = 0;

	BOOK_LIST_FOR_EACH(small, node)
	{
		book_print(node->book);
		printf("Yes or no?");
		printf("1 - yes");
		printf("0 - no");
		scanf("%d", &i);

		if (i == 1) {

			printf("modify the book");
			printf("modify the title?");
			printf("1 - yes");
			printf("0 - no");
			if (getchar() == '1') {
				printf("the title is:");
				free(node->book->title);
				scanf("%80s", input);
				node->book->title = input;
			}

			printf("modify the author?");
			printf("1 - yes");
			printf("0 - no");
			if (getchar() == '1') {
				free(node->book->authors);
				printf(" the first author is:");
				scanf("%80s", input);
				node->book->authors[0] = input;
				printf(" the second author is:");
				scanf("%80s", input);
				node->book->authors[1] = input;
				printf(" the third author is:");
				scanf("%80s", input);
				node->book->authors[2] = input;
				printf(" the fourth author is:");
				scanf("%80s", input);
				node->book->authors[3] = input;
				printf(" the fifth author is:");
				scanf("%80s", input);
				node->book->authors[4] = input;
			}

			printf("modify the number?");
			printf("1 - yes");
			printf("0 - no");
			if (getchar() == '1') {
				printf("the number is:");
				free(node->book->number);
				scanf("%80s", input);
				node->book->number = input;
			}

			printf("modify the subjects?");
			printf("1 - yes");
			printf("0 - no");
			if(getchar() == '1'){
				free(node->book->subjects);
				printf(" the first author is:");
				scanf("%80s", input);
			    node->book->authors[0] = input;
				printf(" the second author is:");
				scanf("%80s", input);
				node->book->authors[1] = input;
				printf(" the third author is:");
				scanf("%80s", input);
				node->book->authors[2] = input;
				printf(" the fourth author is:");
				scanf("%80s", input);
				node->book->authors[3] = input;
				printf(" the fifth author is:");
				scanf("%80s", input);
				node->book->authors[4] = input;
			}

			printf("modify the publisher?");
			printf("1 - yes");
			printf("0 - no");
			if(getchar() == '1'){
				printf("the publisher is:");
				free(node->book->publisher);
				scanf("%80s", input);
				node->book->number = input;
			}

			printf("modify the year?");
			printf("1 - yes");
			printf("0 - no");
			if(getchar() == '1'){
				printf("the year is:");
				free(node->book->year);
				scanf("%80s", input);
				node->book->year = input;
			}

			printf("modify the cirluating?");
			printf("1 - yes");
		    printf("0 - no");
			if(getchar() == '1'){
				printf("the cirluating is:");
				printf("1 - circulating");
				printf("0 - uncirluating");
				scanf("%d", &node->book->circulating);
			}
		}
	}
	book_list_delete(small);
}

void delete_book(BookList* list){
	BookList *small = get_booklist(list);
	BookNode* node;
	int i;

	BOOK_LIST_FOR_EACH(small, node){
		book_print(node->book);
		printf("yes or no?");
		printf("1 - yes");
		printf("0 - no");
		scanf("%d", &i);

		if(i == 1){
			book_list_remove(list, node->book);
		}
	}

	book_list_delete(small);
}

BookList *get_booklist(BookList *list){
	char *input;
	BookNode *node;
	BookList *small;
	int a;

	printf("Select a filter: ");
	printf("1 - title");
	printf("2 - author");
	printf("3 - catalog number");
	printf("4 - subject headings");
	printf("5 - publisher");
	printf("6 - year of publication");
	printf("7 - circulation condition");
	printf("8 - all filters");
	scanf("%d", &a);
	printf("enter your input");
	scanf("%as", &input);

	BOOK_LIST_FOR_EACH(list, node)
	{
		switch (a) {
		case 1:
			small = book_list_search(list, book_filter_title, input);
			break;
		case 2:
			small = book_list_search(list, book_filter_authors, input);
			break;
		case 3:
			small = book_list_search(list, book_filter_number, input);
			break;
		case 4:
			small = book_list_search(list, book_filter_subjects, input);
			break;
		case 5:
			small = book_list_search(list, book_filter_publisher, input);
			break;
		case 6:
			small = book_list_search(list, book_filter_year, input);
			break;
		case 7:
			small = book_list_search(list, book_filter_circulating,
					input);
			break;
		case 8:
			small = book_list_search(list, book_filter_string, input);
			break;
		}
	}
	if (sizeof(small) == 0) {
		return NULL;
	} else {
		return small;
	}
}

void search_book(BookList *list) {
	BookList *small = get_booklist(list);
	BookNode* node;
	BOOK_LIST_FOR_EACH(small, node)
	{
		book_print(node->book);
	}
	book_list_delete(small);
}
