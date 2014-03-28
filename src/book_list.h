/*
 * File: book_list.h
 * Author: Zhang Hai
 */

#ifndef _LMS_BOOK_LIST_H_
#define _LMS_BOOK_LIST_H_


#include "common.h"

#include "book.h"


#define BOOK_LIST_FOR_EACH(list, node) \
    for (node = list->head; node != NULL; node = node->next)


typedef struct tagBookNode BookNode;
typedef struct tagBookNode {
    Book *book;
    BookNode *prev;
    BookNode *next;
} BookNode;

typedef struct {
    BookNode *head;
    BookNode *tail;
    size_t size;
} BookList;


BookList *book_list_new();

void book_list_delete(BookList *list);

BOOL book_list_serialize(BookList *list, FILE *file);

BookList *book_list_deserialize(FILE *file);

BookNode *book_list_add_start(BookList *list, Book *book);

BookNode *book_list_add_end(BookList *list, Book *book);

BookNode *book_list_insert_before(BookList *list, BookNode *node,
        Book *book);

BookNode *book_list_insert_after(BookList *list, BookNode *node,
        Book *book);

BookNode *book_list_remove_node(BookList *list, BookNode *node);

void book_list_swap(BookList *list, BookNode *node1,
        BookNode *node2);

void book_list_sort(BookList *list,
        int (*comparator)(BookNode *node1, BookNode *node2));

BookList *book_list_search(BookList *list,
        BOOL (*filter)(Book *book, void *criteria), void *criteria);


#endif /* _LMS_BOOK_LIST_H_ */
