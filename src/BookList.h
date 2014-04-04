/**
 * @file BookList.h
 * @author Zhang Hai
 */

#ifndef _BOOK_LIST_H_
#define _BOOK_LIST_H_


#include "Library/Common.h"

#include "Library/LinkedList.h"

#include "Book.h"


#define BOOK_LIST_FOR_EACH(list, node) \
    for (node = _(list, head); node != null; node = node->next)


typedef struct tagBookListNode BookListNode;
typedef struct tagBookListNode {
    Book *book;
    BookListNode *prev;
    BookListNode *next;
} BookListNode;


typedef struct {
    BookListNode *head;
    BookListNode *tail;
    size_t size;
} BookList_Fields;


typedef struct tagBookList BookList;

typedef BookList *(*BookList_MethodNew)();
typedef void (*BookList_MethodDelete)(BookList *this);
typedef BookListNode *(*BookList_MethodNewNode)(Book *book,
        BookListNode *previous, BookListNode *next);
typedef void (*BookList_MethodDeleteNode)(BookListNode *node);
typedef BookListNode *(*BookList_MethodAddStart)(BookList *this,
        Book *book);
typedef BookListNode *(*BookList_MethodAddEnd)(BookList *this,
        Book *book);
typedef BookListNode *(*BookList_MethodInsertBefore)(BookList *this,
        BookListNode *node, Book *book);
typedef BookListNode *(*BookList_MethodInsertAfter)(BookList *this,
        BookListNode *node, Book *book);
typedef BookListNode *(*BookList_MethodRemoveNode)(BookList *this,
        BookListNode *node);
typedef void (*BookList_MethodRemove)(BookList *this, Book *book);
typedef void (*BookList_MethodSwap)(BookList *this,
        BookListNode *node1, BookListNode *node2);
typedef void (*BookList_MethodSort)(BookList *this,
        BookComparator comparator);
typedef BookList *(*BookList_MethodSearch)(BookList *this,
        BookFilter filter);
typedef bool (*BookList_MethodSerialize)(BookList *this, FILE *file);
typedef BookList *(*BookList_MethodDeserialize)(FILE *file);

typedef struct {

    BookList_MethodNew new;
    BookList_MethodDelete delete;
    BookList_MethodNewNode newNode;
    BookList_MethodDeleteNode deleteNode;
    BookList_MethodAddStart addStart;
    BookList_MethodAddEnd addEnd;
    BookList_MethodInsertBefore insertBefore;
    BookList_MethodInsertAfter insertAfter;
    BookList_MethodRemoveNode removeNode;
    BookList_MethodRemove remove;
    BookList_MethodSwap swap;
    BookList_MethodSort sort;
    BookList_MethodSearch search;

    BookList_MethodSerialize serialize;
    BookList_MethodDeserialize deserialize;
} BookList_Methods;


typedef struct tagBookList {
    BookList_Fields *fields;
    BookList_Methods *methods;
} BookList;

void BookList_initialize(BookList *this);

void BookList_finalize(BookList *this);

BookList *BookList_new();

void BookList_delete(BookList *this);

BookListNode *BookList_newNode(Book *book, BookListNode *previous,
        BookListNode *next);

void BookList_deleteNode(BookListNode *node);

bool BookList_serialize(BookList *this, FILE *file);

BookList *BookList_deserialize(FILE *file);

BookListNode *BookList_addStart(BookList *this, Book *book);

BookListNode *BookList_addEnd(BookList *this, Book *book);

BookListNode *BookList_insertBefore(BookList *this, BookListNode *node,
        Book *book);

BookListNode *BookList_insertAfter(BookList *this, BookListNode *node,
        Book *book);

BookListNode *BookList_removeNode(BookList *this, BookListNode *node);

void BookList_remove(BookList *this, Book *book);

void BookList_swap(BookList *this, BookListNode *node1,
        BookListNode *node2);

void BookList_sort(BookList *this, BookComparator comparator);

BookList *BookList_search(BookList *this, BookFilter filter);


#endif /* _BOOK_LIST_H_ */
