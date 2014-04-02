/*
 * File: BookList.c
 * Author: Zhang Hai
 */

#include "BookList.h"


BookNode *BookNode_new(void *data, BookNode *prev, BookNode *next) {
    Book_addReference(data);
    return LinkedListNode_new(data, (LinkedListNode *)prev,
            (LinkedListNode *)next);
}

void BookNode_delete(BookNode *node) {
    Book_removeReference(node->data);
    LinkedListNode_delete((LinkedListNode *)node);
}

/**
 * Create a new instance of {@link BookList}.
 * @return The created {@link BookList} instance.
 */
BookList *BookList_new() {

    BookList *list = Memory_allocateType(BookList);

    LinkedList_initialize(list,
            (LinkedList_MethodNew) BookList_new,
            (LinkedList_MethodDelete) BookList_delete,
            (LinkedList_MethodNewNode) BookNode_new,
            (LinkedList_MethodDeleteNode) BookNode_delete,
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
 * Destroy a {@link BookList} instance.
 * @param list The {@link BookList} instance to be destroyed.
 */
void BookList_delete(BookList *list) {

    LinkedList_finalize((LinkedList *)list);

    Memory_free(list);
}

/**
 * Serialize a {@link BookList} to file.
 * @param list The {@link BookList} to be serialized.
 * @param file The file to serialize {@param list}.
 * @return Whether the serialization was successful.
 */
bool BookList_serialize(BookList *list, FILE *file) {

    BookNode *node;

    size_t_serialize(&list->size, file);
    BOOK_LIST_FOR_EACH(list, node) {
        if (!Book_serialize(node->data, file)) {
            return false;
        }
    }

    return true;
}

/**
 * Deserialize a {@link BookList} from file.
 * @param file The file to deserialize a {@link BookList} from.
 * @return a {@link BookList} deserialized from {@param file}, or null
 *         if failed to read sufficient data.
 */
BookList *BookList_deserialize(FILE *file) {

    BookList *list = BookList_new();
    size_t size, i;
    Book *book;

    if (!size_t_deserialize(&size, file)) {
        return null;
    }
    for (i = 0; i < size; ++i) {
        if ((book = Book_deserialize(file)) == null) {
            return null;
        }
        BookList_addEnd(list, book);
        Book_removeReference(book);
    }

    return list;
}

/**
 * Add a {@link Book} instance to the start of a {@link BookList}.
 * @param list The {@link BookList} to add {@param book} to.
 * @param book The {@link Book} to be added.
 * @return The newly added node in the {@param list}.
 */
BookNode *BookList_addStart(BookList *list, Book *book) {
    return LinkedList_addStart((LinkedList *)list, book);
}

/**
 * Add a {@link Book} instance to the end of a {@link BookList}.
 * @param list The {@link BookList} to add {@param book} to.
 * @param book The {@link Book} to be added.
 * @return The newly added node in the {@param list}.
 */
BookNode *BookList_addEnd(BookList *list, Book *book) {
    return LinkedList_addEnd((LinkedList *)list, book);
}

/**
 * Insert a {@link Book} instance before {@param node}.
 * @param list The {@link BookList} to insert {@param book} into.
 * @param node The node to insert before.
 * @param book The {@link Book} to be inserted.
 * @return The newly inserted node in the {@param list}.
 */
BookNode *BookList_insertBefore(BookList *list, BookNode *node,
        Book *book) {
    return LinkedList_insertBefore((LinkedList *)list,
            (LinkedListNode *)node, book);
}

/**
 * Insert a {@link Book} instance after {@param node}.
 * @param list The {@link BookList} to insert {@param book} into.
 * @param node The node to insert after.
 * @param book The {@link Book} to be inserted.
 * @return The newly inserted node in the {@param list}.
 */
BookNode *BookList_insertAfter(BookList *list, BookNode *node,
        Book *book) {
    return LinkedList_insertAfter((LinkedList *)list,
            (LinkedListNode *)node, book);
}

/**
 * Remove {@param node} from a {@link BookList}.
 * @param list The {@link BookList} to remove the node from.
 * @param node The node to be removed.
 * @return the node following the removed one, or null if the tail
 *         node is removed.
 */
BookNode *BookList_removeNode(BookList *list, BookNode *node) {
    return LinkedList_removeNode((LinkedList *)list,
            (LinkedListNode *)node);
}

/**
 * Remove a {@link Book} instance from a {@link BookList}.
 * @note This function will only remove the first occurrence of
 *       {@param Book}.
 * @param list The {@link BookList} to remove {@param book} from.
 * @param book The {@link Book} instance to be removed.
 */
void BookList_remove(BookList *list, Book *book) {
    LinkedList_remove((LinkedList *)list, book);
}

/**
 * Swap two nodes in a {@link BookList}.
 * @note This function will simply swap the {@link Book} objects of
 *       the two nodes.
 * @param node1 The first node to be swapped.
 * @param node2 The second node to be swapped.
 */
void BookList_swap(BookList *list, BookNode *node1,
        BookNode *node2) {
    LinkedList_swap((LinkedList *)list, (LinkedListNode *)node1,
            (LinkedListNode *)node2);
}

/**
 * Sort a {@link BookList} by a comparator.
 * @note This function uses bubble sort.
 * @param list The {@link BookList} to be sorted.
 * @param comparator The comparator for sorting.
 */
void BookList_sort(BookList *list, BookComparator comparator) {
    LinkedList_sort((LinkedList *)list, (Comparator) comparator);
}

/**
 * Search in a {@link BookList} by a filter.
 * @param list The {@link BookList} to be searched in.
 * @param filter A filter function for the search.
 * @param criteria The criteria data to be passed into
 *        {@param filter}.
 * @return A {@link BookList} containing the result.
 */
BookList *BookList_search(BookList *list, BookFilter filter) {
    return LinkedList_search((LinkedList *)list, *(Filter *)&filter);
}
