/*
 * File: LinkedList.h
 * Author: Zhang Hai
 */

#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_


#include "Common.h"


#define LINKED_LIST_FOR_EACH(list, node) \
    for (node = list->head; node != NULL; node = node->next)


typedef struct tagLinkedListNode LinkedListNode;
typedef struct tagLinkedListNode {
    void *data;
    LinkedListNode *prev;
    LinkedListNode *next;
} LinkedListNode;

typedef struct {
    LinkedListNode *head;
    LinkedListNode *tail;
    size_t size;
} LinkedList;


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

void LinkedList_sort(LinkedList *list,
        int (*comparator)(void *data1, void *data2));

LinkedList *LinkedList_search(LinkedList *list,
        BOOL (*filter)(void *data, void *criteria), void *criteria);


#endif /* _LINKED_LIST_H_ */
