/*
 * File: BookList.c
 * Author: Zhang Hai
 */

#include "BookList.h"


/**
 * Create a new instance of {@link BookList}.
 * @return The created {@link BookList} instance.
 */
BookList *BookList_new() {
    return LinkedList_new();
}

/**
 * Destroy a {@link BookList} instance.
 * @param list The {@link BookList} instance to be destroyed.
 */
void BookList_delete(BookList *list) {

    BookNode *node;
    BOOK_LIST_FOR_EACH(list, node) {
        Book_removeReference(node->data);
    }

    LinkedList_delete(list);
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

    Book_addReference(book);

    return LinkedList_addStart(list, book);
}

/**
 * Add a {@link Book} instance to the end of a {@link BookList}.
 * @param list The {@link BookList} to add {@param book} to.
 * @param book The {@link Book} to be added.
 * @return The newly added node in the {@param list}.
 */
BookNode *BookList_addEnd(BookList *list, Book *book) {

    Book_addReference(book);

    return LinkedList_addEnd(list, book);
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

    Book_addReference(book);

    return LinkedList_insertBefore(list, node, book);
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

    Book_addReference(book);

    return LinkedList_insertAfter(list, node, book);
}

/**
 * Remove {@param node} from a {@link BookList}.
 * @param list The {@link BookList} to remove the node from.
 * @param node The node to be removed.
 * @return the node following the removed one, or null if the tail
 *         node is removed.
 */
BookNode *BookList_removeNode(BookList *list, BookNode *node) {

    Book_removeReference(node->data);

    return LinkedList_removeNode(list, node);
}

/**
 * Remove a {@link Book} instance from a {@link BookList}.
 * @note This function will only remove the first occurrence of
 *       {@param Book}.
 * @param list The {@link BookList} to remove {@param book} from.
 * @param book The {@link Book} instance to be removed.
 */
void BookList_remove(BookList *list, Book *book) {
    BookNode *node;
    BOOK_LIST_FOR_EACH(list, node) {
        if (node->data == book) {
            BookList_removeNode(list, node);
            return;
        }
    }
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
    LinkedList_swap(list, node1, node2);
}

/**
 * Sort a {@link BookList} by a comparator.
 * @note This function uses bubble sort.
 * @param list The {@link BookList} to be sorted.
 * @param comparator The comparator for sorting.
 */
void BookList_sort(BookList *list, BookComparator comparator) {
    LinkedList_sort(list, (Comparator) comparator);
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
    return LinkedList_search(list, *(Filter *)&filter);
}
