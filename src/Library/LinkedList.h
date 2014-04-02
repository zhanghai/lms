/*
 * File: LinkedList.h
 * Author: Zhang Hai
 */

#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_


#include "Common.h"


#define LINKED_LIST_FOR_EACH(list, node) \
    for (node = list->head; node != null; node = node->next)


typedef struct tagLinkedListNode LinkedListNode;
typedef struct tagLinkedListNode {
    void *data;
    LinkedListNode *prev;
    LinkedListNode *next;
} LinkedListNode;

typedef struct tagLinkedList LinkedList;

typedef LinkedList *(*LinkedList_MethodNew)();
typedef void (*LinkedList_MethodDelete)(LinkedList *list);
typedef LinkedListNode *(*LinkedList_MethodNewNode)(void *data,
        LinkedListNode *prev,
        LinkedListNode *next);
typedef void (*LinkedList_MethodDeleteNode)(
        LinkedListNode *node);
typedef LinkedListNode *(*LinkedList_MethodAddStart)(
        LinkedList *list, void *data);
typedef LinkedListNode *(*LinkedList_MethodAddEnd)(LinkedList *list,
        void *data);
typedef LinkedListNode *(*LinkedList_MethodInsertBefore)(
        LinkedList *list, LinkedListNode *node, void *data);
typedef LinkedListNode *(*LinkedList_MethodInsertAfter)(
        LinkedList *list, LinkedListNode *node, void *data);
typedef LinkedListNode *(*LinkedList_MethodRemoveNode)(
        LinkedList *list, LinkedListNode *node);
typedef void (*LinkedList_MethodRemove)(LinkedList *list,
        void *data);
typedef void (*LinkedList_MethodSwap)(LinkedList *list,
        LinkedListNode *node1, LinkedListNode *node2);
typedef void (*LinkedList_MethodSort)(LinkedList *list,
        Comparator comparator);
typedef LinkedList *(*LinkedList_MethodSearch)(LinkedList *list,
        Filter filter);

typedef struct {
    LinkedList_MethodNew new;
    LinkedList_MethodDelete delete;
    LinkedList_MethodNewNode newNode;
    LinkedList_MethodDeleteNode deleteNode;
    LinkedList_MethodAddStart addStart;
    LinkedList_MethodAddEnd addEnd;
    LinkedList_MethodInsertBefore insertBefore;
    LinkedList_MethodInsertAfter insertAfter;
    LinkedList_MethodRemoveNode removeNode;
    LinkedList_MethodRemove remove;
    LinkedList_MethodSwap swap;
    LinkedList_MethodSort sort;
    LinkedList_MethodSearch search;
} LinkedListMethods;

typedef struct tagLinkedList {
    LinkedListNode *head;
    LinkedListNode *tail;
    size_t size;
    /**
     * @protected The following function table are intended only for
     *            subclass to use.
     * @note You should not add any member after it.
     */
    LinkedListMethods methods;
} LinkedList;


LinkedListNode *LinkedListNode_new(void *data, LinkedListNode *prev,
        LinkedListNode *next);

void LinkedListNode_delete(LinkedListNode *node);

void LinkedList_initialize(LinkedList *list,
        LinkedList_MethodNew new,
        LinkedList_MethodDelete delete,
        LinkedList_MethodNewNode newNode,
        LinkedList_MethodDeleteNode deleteNode,
        LinkedList_MethodAddStart addStart,
        LinkedList_MethodAddEnd addEnd,
        LinkedList_MethodInsertBefore insertBefore,
        LinkedList_MethodInsertAfter insertAfter,
        LinkedList_MethodRemoveNode removeNode,
        LinkedList_MethodRemove remove,
        LinkedList_MethodSwap swap,
        LinkedList_MethodSort sort,
        LinkedList_MethodSearch search);

void LinkedList_finalize(LinkedList *list);

LinkedList *LinkedList_new();

void LinkedList_delete(LinkedList *list);

LinkedListNode *LinkedList_addStart(LinkedList *list, void *data);

LinkedListNode *LinkedList_addEnd(LinkedList *list, void *data);

LinkedListNode *LinkedList_insertBefore(LinkedList *list,
        LinkedListNode *node, void *data);

LinkedListNode *LinkedList_insertAfter(LinkedList *list,
        LinkedListNode *node, void *data);

LinkedListNode *LinkedList_removeNode(LinkedList *list,
        LinkedListNode *node);

void LinkedList_remove(LinkedList *list, void *data);

void LinkedList_swap(LinkedList *list, LinkedListNode *node1,
        LinkedListNode *node2);

void LinkedList_sort(LinkedList *list, Comparator comparator);

LinkedList *LinkedList_search(LinkedList *list, Filter filter);


#endif /* _LINKED_LIST_H_ */
