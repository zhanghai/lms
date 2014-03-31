/*
 * File: LinkedList.c
 * Author: Zhang Hai
 */

#include "LinkedList.h"


static LinkedListNode *LinkedListNode_new(void *data, LinkedListNode *prev,
        LinkedListNode *next);
static void LinkedListNode_delete(LinkedListNode *node);


static LinkedListNode *LinkedListNode_new(void *data, LinkedListNode *prev,
        LinkedListNode *next) {

    LinkedListNode *node = LMS_NEW(LinkedListNode);

    node->data = data;
    node->prev = prev;
    node->next = next;

    return node;
}

static void LinkedListNode_delete(LinkedListNode *node) {
    free(node);
}

/**
 * Create a new instance of {@link LinkedList}.
 * @return The created {@link LinkedList} instance.
 */
LinkedList *LinkedList_new() {

    LinkedList *list = LMS_NEW(LinkedList);

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

/**
 * Destroy a {@link LinkedList} instance.
 * @param list The {@link LinkedList} instance to be destroyed.
 */
void LinkedList_delete(LinkedList *list) {

    LinkedListNode *node;
    LINKED_LIST_FOR_EACH(list, node) {
        LinkedListNode_delete(node);
    }

    free(list);
}

/**
 * Add a node holding {@param data} to the start of a
 * {@link LinkedList}.
 * @param list The {@link LinkedList} to add {@param data} to.
 * @param data The data to be added.
 * @return The newly added node in the {@param list}.
 */
LinkedListNode *LinkedList_addStart(LinkedList *list, void *data) {

    LinkedListNode *node = LinkedListNode_new(data, NULL,
            list->head);

    if (list->head != NULL) {
        list->head->prev = node;
    }

    list->head = node;
    if (list->tail == NULL) {
        list->tail = node;
    }

    ++list->size;

    return node;
}

/**
 * Add a node holding {@param data} to the end of a
 * {@link LinkedList}.
 * @param list The {@link LinkedList} to add {@param data} to.
 * @param data The data to be added.
 * @return The newly added node in the {@param list}.
 */
LinkedListNode *LinkedList_addEnd(LinkedList *list, void *data) {

    LinkedListNode *node = LinkedListNode_new(data, list->tail, NULL);

    if (list->tail != NULL) {
        list->tail->next = node;
    }

    list->tail = node;
    if (list->head == NULL) {
        list->head = node;
    }

    ++list->size;

    return node;
}

/**
 * Insert a new node holding {@param data} before {@param node}.
 * @param list The {@link LinkedList} to insert {@param data} into.
 * @param node The node to insert before.
 * @param data The data to be inserted.
 * @return The newly inserted node in the {@param list}.
 */
LinkedListNode *LinkedList_insertBefore(LinkedList *list, LinkedListNode *node,
        void *data) {

    LinkedListNode *newNode = LinkedListNode_new(data, node->prev, node);

    if (node->prev != NULL) {
        node->prev->next = newNode;
    } else {
        list->head = newNode;
    }
    node->prev = newNode;

    ++list->size;

    return newNode;
}

/**
 * Insert a new node holding {@param data} after {@param node}.
 * @param list The {@link LinkedList} to insert {@param data} into.
 * @param node The node to insert after.
 * @param data The data to be inserted.
 * @return The newly inserted node in the {@param list}.
 */
LinkedListNode *LinkedList_insertAfter(LinkedList *list, LinkedListNode *node,
        void *data) {

    LinkedListNode *newNode = LinkedListNode_new(data, node, node->next);

    if (node->next != NULL) {
        node->next->prev = newNode;
    } else {
        list->tail = newNode;
    }
    node->next = newNode;

    ++list->size;

    return newNode;
}

/**
 * Remove {@param node} from a {@link LinkedList}.
 * @param list The {@link LinkedList} to remove the node from.
 * @param node The node to be removed.
 * @return the node following the removed one, or NULL if the tail
 *         node is removed.
 */
LinkedListNode *LinkedList_removeNode(LinkedList *list, LinkedListNode *node) {

    LinkedListNode *nextNode = node->next;

    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    LinkedListNode_delete(node);

    --list->size;

    return nextNode;
}

/**
 * Remove {@param data} from a {@link LinkedList}.
 * @note This function will only remove the first occurrence of
 *       {@param data}.
 * @param list The {@link LinkedList} to remove {@param data} from.
 * @param data The data to be removed.
 */
void LinkedList_remove(LinkedList *list, void *data) {
    LinkedListNode *node;
    LINKED_LIST_FOR_EACH(list, node) {
        if (node->data == data) {
            LinkedList_removeNode(list, node);
            return;
        }
    }
}

/**
 * Swap two nodes in a {@link LinkedList}.
 * @note This function will simply swap the data of the two nodes.
 * @param node1 The first node to be swapped.
 * @param node2 The second node to be swapped.
 */
void LinkedList_swap(LinkedList *list, LinkedListNode *node1,
        LinkedListNode *node2) {
    void *tmp;
    LMS_SWAP(node1->data, node2->data, tmp);
}

/**
 * Sort a {@link LinkedList} by a comparator.
 * @note This function uses bubble sort.
 * @param list The {@link LinkedList} to be sorted.
 * @param comparator The comparator for sorting.
 */
void LinkedList_sort(LinkedList *list,
        int (*comparator)(void *data1, void *data2)) {

    LinkedListNode *node1, *node2;
    BOOL changed;

    if (list->size == 0) {
        return;
    }

    for (node1 = list->head; node1->next != NULL;
            node1 = node1->next) {

        changed = FALSE;

        for (node2 = list->tail; node2 != node1; ) {
            if (comparator(node2->prev->data, node2->data) > 0) {
                LinkedList_swap(list, node2->prev, node2);
                changed = TRUE;
            } else {
                node2 = node2->prev;
            }
        }

        if (!changed) {
            break;
        }
    }
}

/**
 * Search in a {@link LinkedList} by a filter.
 * @param list The {@link LinkedList} to be searched in.
 * @param filter A filter function for the search.
 * @param criteria The criteria data to be passed into
 *        {@param filter}.
 * @return A {@link LinkedList} containing the result.
 */
LinkedList *LinkedList_search(LinkedList *list,
        BOOL (*filter)(void *data, void *criteria), void *criteria) {

    LinkedList *result = LinkedList_new();
    LinkedListNode *node;

    LINKED_LIST_FOR_EACH(list, node) {
        if (filter(node->data, criteria)) {
            LinkedList_addEnd(result, node->data);
        }
    }

    return result;
}
