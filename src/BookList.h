/*
 * File: BookList.h
 * Author: Zhang Hai
 */

#ifndef _BOOK_LIST_H_
#define _BOOK_LIST_H_


#include "Library/Common.h"

#include "Library/LinkedList.h"

#include "Book.h"


#define BOOK_LIST_FOR_EACH(list, node) \
    for (node = list->head; node != null; node = node->next)


typedef LinkedListNode BookNode;

typedef LinkedList BookList;


BookNode *BookNode_new(void *data, BookNode *prev, BookNode *next);

void BookNode_delete(BookNode *node);

BookList *BookList_new();

void BookList_delete(BookList *list);

bool BookList_serialize(BookList *list, FILE *file);

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

void BookList_sort(BookList *list, BookComparator comparator);

BookList *BookList_search(BookList *list, BookFilter filter);


#endif /* _BOOK_LIST_H_ */
