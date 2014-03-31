/*
 * File: BookList.h
 * Author: Zhang Hai
 */

#ifndef _BOOK_LIST_H_
#define _BOOK_LIST_H_


#include "Common.h"

#include "Book.h"


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


BookList *BookList_new();

void BookList_delete(BookList *list);

BOOL BookList_serialize(BookList *list, FILE *file);

BookList *BookList_deserialize(FILE *file);

BookNode *BookList_addStart(BookList *list, Book *book);

BookNode *BookList_addEnd(BookList *list, Book *book);

BookNode *BookList_insertBefore(BookList *list, BookNode *node,
        Book *book);

BookNode *BookList_insertAfter(BookList *list, BookNode *node,
        Book *book);

BookNode *BookList_removeNode(BookList *list, BookNode *node);

void BookList_remove(BookList *list, Book *book);

void BookList_swap(BookList *list, BookNode *node1,
        BookNode *node2);

void BookList_sort(BookList *list,
        int (*comparator)(Book *book1, Book *book2));

BookList *BookList_search(BookList *list,
        BOOL (*filter)(Book *book, void *criteria), void *criteria);


#endif /* _BOOK_LIST_H_ */
