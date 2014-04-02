/**
 * @file LinkedList.c
 * @author Zhang Hai
 */

#include "LinkedList.h"


LinkedListNode *LinkedListNode_new(void *data, LinkedListNode *prev,
        LinkedListNode *next) {

    LinkedListNode *node = Memory_allocateType(LinkedListNode);

    node->data = data;
    node->prev = prev;
    node->next = next;

    return node;
}

void LinkedListNode_delete(LinkedListNode *node) {
    Memory_free(node);
}

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
        LinkedList_MethodSearch search) {
    list->head = null;
    list->tail = null;
    list->size = 0;
    list->methods.new = new;
    list->methods.delete = delete;
    list->methods.newNode = newNode;
    list->methods.deleteNode = deleteNode;
    list->methods.addStart = addStart;
    list->methods.addEnd = addEnd;
    list->methods.insertBefore = insertBefore;
    list->methods.insertAfter = insertAfter;
    list->methods.removeNode = removeNode;
    list->methods.remove = remove;
    list->methods.swap = swap;
    list->methods.sort = sort;
    list->methods.search = search;
}

void LinkedList_finalize(LinkedList *list) {
    LinkedListNode *node;
    LINKED_LIST_FOR_EACH(list, node) {
        list->methods.deleteNode(node);
    }
}

/**
 * Create a new instance of {@link LinkedList}.
 * @return The created {@link LinkedList} instance.
 */
LinkedList *LinkedList_new() {

    LinkedList *list = Memory_allocateType(LinkedList);

    LinkedList_initialize(list,
            LinkedList_new,
            LinkedList_delete,
            LinkedListNode_new,
            LinkedListNode_delete,
            LinkedList_addStart,
            LinkedList_addEnd,
            LinkedList_insertBefore,
            LinkedList_insertAfter,
            LinkedList_removeNode,
            LinkedList_remove,
            LinkedList_swap,
            LinkedList_sort,
            LinkedList_search);

    return list;
}

/**
 * Destroy a {@link LinkedList} instance.
 * @param list The {@link LinkedList} instance to be destroyed.
 */
void LinkedList_delete(LinkedList *list) {

    LinkedList_finalize(list);

    Memory_free(list);
}

/**
 * Add a node holding some data to the start of a {@link LinkedList}.
 * @param list The {@link LinkedList} to add the data to.
 * @param data The data to be added.
 * @return The newly added node in the {@link LinkedList}.
 */
LinkedListNode *LinkedList_addStart(LinkedList *list, void *data) {

    LinkedListNode *node = list->methods.newNode(data, null,
            list->head);

    if (list->head != null) {
        list->head->prev = node;
    }

    list->head = node;
    if (list->tail == null) {
        list->tail = node;
    }

    ++list->size;

    return node;
}

/**
 * Add a node holding some data to the end of a {@link LinkedList}.
 * @param list The {@link LinkedList} to add the data to.
 * @param data The data to be added.
 * @return The newly added node in the {@link LinkedList}.
 */
LinkedListNode *LinkedList_addEnd(LinkedList *list, void *data) {

    LinkedListNode *node = list->methods.newNode(data, list->tail,
            null);

    if (list->tail != null) {
        list->tail->next = node;
    }

    list->tail = node;
    if (list->head == null) {
        list->head = node;
    }

    ++list->size;

    return node;
}

/**
 * Insert a new node holding some data before a node.
 * @param list The {@link LinkedList} to insert the data into.
 * @param node The node to insert before.
 * @param data The data to be inserted.
 * @return The newly inserted node in the {@link LinkedList}.
 */
LinkedListNode *LinkedList_insertBefore(LinkedList *list,
        LinkedListNode *node, void *data) {

    LinkedListNode *newNode = list->methods.newNode(data, node->prev,
            node);

    if (node->prev != null) {
        node->prev->next = newNode;
    } else {
        list->head = newNode;
    }
    node->prev = newNode;

    ++list->size;

    return newNode;
}

/**
 * Insert a new node holding some data after a node.
 * @param list The {@link LinkedList} to insert the data into.
 * @param node The node to insert after.
 * @param data The data to be inserted.
 * @return The newly inserted node in the {@link LinkedList}.
 */
LinkedListNode *LinkedList_insertAfter(LinkedList *list, LinkedListNode *node,
        void *data) {

    LinkedListNode *newNode = list->methods.newNode(data, node,
            node->next);

    if (node->next != null) {
        node->next->prev = newNode;
    } else {
        list->tail = newNode;
    }
    node->next = newNode;

    ++list->size;

    return newNode;
}

/**
 * Remove a node from a {@link LinkedList}.
 * @param list The {@link LinkedList} to remove the node from.
 * @param node The node to be removed.
 * @return the node following the removed one, or null if the tail
 *         node is removed.
 */
LinkedListNode *LinkedList_removeNode(LinkedList *list, LinkedListNode *node) {

    LinkedListNode *nextNode = node->next;

    if (node->prev != null) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }
    if (node->next != null) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    list->methods.deleteNode(node);

    --list->size;

    return nextNode;
}

/**
 * Remove a piece of data from a {@link LinkedList}.
 * @note This function will only remove the first occurrence of the
 *       data.
 * @param list The {@link LinkedList} to remove the data from.
 * @param data The data to be removed.
 */
void LinkedList_remove(LinkedList *list, void *data) {
    LinkedListNode *node;
    LINKED_LIST_FOR_EACH(list, node) {
        if (node->data == data) {
            list->methods.removeNode(list, node);
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
    SWAP(node1->data, node2->data, tmp);
}

/**
 * Sort a {@link LinkedList} by a comparator.
 * @note This function uses bubble sort.
 * @param list The {@link LinkedList} to be sorted.
 * @param comparator The comparator for sorting.
 */
void LinkedList_sort(LinkedList *list, Comparator comparator) {

    LinkedListNode *node1, *node2;
    bool changed;

    if (list->size == 0) {
        return;
    }

    for (node1 = list->head; node1->next != null;
            node1 = node1->next) {

        changed = false;

        for (node2 = list->tail; node2 != node1; ) {
            if (comparator(node2->prev->data, node2->data) > 0) {
                list->methods.swap(list, node2->prev, node2);
                changed = true;
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
 * @param criteria The criteria data to be passed into the filter.
 * @return A {@link LinkedList} containing the result.
 */
LinkedList *LinkedList_search(LinkedList *list, Filter filter) {

    LinkedList *result = list->methods.new();
    LinkedListNode *node;

    LINKED_LIST_FOR_EACH(list, node) {
        if (filter.filter(node->data, filter.filterData)) {
            list->methods.addEnd(result, node->data);
        }
    }

    return result;
}
