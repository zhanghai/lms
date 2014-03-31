/*
 * File: BookList.c
 * Author: Zhang Hai
 */

#include "BookList.h"


static BookNode *BookNode_new(Book *book, BookNode *prev,
        BookNode *next);
static void BookNode_delete(BookNode *node);


static BookNode *BookNode_new(Book *book, BookNode *prev,
        BookNode *next) {

    BookNode *node = LMS_NEW(BookNode);

    Book_addReference(book);
    node->book = book;
    node->prev = prev;
    node->next = next;

    return node;
}

static void BookNode_delete(BookNode *node) {

    Book_removeReference(node->book);

    free(node);
}

/**
 * Create a new instance of {@link BookList}.
 * @return The created {@link BookList} instance.
 */
BookList *BookList_new() {

    BookList *list = LMS_NEW(BookList);

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

/**
 * Destroy a {@link BookList} instance.
 * @param list The {@link BookList} instance to be destroyed.
 */
void BookList_delete(BookList *list) {

    BookNode *node;
    BOOK_LIST_FOR_EACH(list, node) {
        BookNode_delete(node);
    }

    free(list);
}

/**
 * Serialize a {@link BookList} to file.
 * @param list The {@link BookList} to be serialized.
 * @param file The file to serialize {@param list}.
 * @return Whether the serialization was successful.
 */
BOOL BookList_serialize(BookList *list, FILE *file) {
    BookNode *node;
    serialize_size(&list->size, file);
    BOOK_LIST_FOR_EACH(list, node) {
        if (!Book_serialize(node->book, file)) {
            return FALSE;
        }
    }
    return TRUE;
}

/**
 * Deserialize a {@link BookList} from file.
 * @param file The file to deserialize a {@link BookList} from.
 * @return a {@link BookList} deserialized from {@param file}, or NULL
 *         if failed to read sufficient data.
 */
BookList *BookList_deserialize(FILE *file) {

    BookList *list = BookList_new();
    size_t size, i;
    Book *book;

    if (!deserialize_size(&size, file)) {
        return NULL;
    }
    for (i = 0; i < size; ++i) {
        if ((book = Book_deserialize(file)) == NULL) {
            return NULL;
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

    BookNode *node = BookNode_new(book, NULL,
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
 * Add a {@link Book} instance to the end of a {@link BookList}.
 * @param list The {@link BookList} to add {@param book} to.
 * @param book The {@link Book} to be added.
 * @return The newly added node in the {@param list}.
 */
BookNode *BookList_addEnd(BookList *list, Book *book) {

    BookNode *node = BookNode_new(book, list->tail, NULL);

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
 * Insert a {@link Book} instance before {@param node}.
 * @param list The {@link BookList} to insert {@param book} into.
 * @param node The node to insert before.
 * @param book The {@link Book} to be inserted.
 * @return The newly inserted node in the {@param list}.
 */
BookNode *BookList_insertBefore(BookList *list, BookNode *node,
        Book *book) {

    BookNode *newNode = BookNode_new(book, node->prev, node);

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
 * Insert a {@link Book} instance after {@param node}.
 * @param list The {@link BookList} to insert {@param book} into.
 * @param node The node to insert after.
 * @param book The {@link Book} to be inserted.
 * @return The newly inserted node in the {@param list}.
 */
BookNode *BookList_insertAfter(BookList *list, BookNode *node,
        Book *book) {

    BookNode *newNode = BookNode_new(book, node, node->next);

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
 * Remove {@param node} from a {@link BookList}.
 * @param list The {@link BookList} to remove the node from.
 * @param node The node to be removed.
 * @return the node following the removed one, or NULL if the tail
 *         node is removed.
 */
BookNode *BookList_removeNode(BookList *list, BookNode *node) {

    BookNode *nextNode = node->next;

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

    BookNode_delete(node);

    --list->size;

    return nextNode;
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
        if (node->book == book) {
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
    Book *tmp;
    LMS_SWAP(node1->book, node2->book, tmp);
}

/**
 * Sort a {@link BookList} by a comparator.
 * @note This function uses bubble sort.
 * @param list The {@link BookList} to be sorted.
 * @param comparator The comparator for sorting.
 */
void BookList_sort(BookList *list,
        int (*comparator)(Book *book1, Book *book2)) {

    BookNode *node1, *node2;
    BOOL changed;

    if (list->size == 0) {
        return;
    }

    for (node1 = list->head; node1->next != NULL;
            node1 = node1->next) {

        changed = FALSE;

        for (node2 = list->tail; node2 != node1; ) {
            if (comparator(node2->prev->book, node2->book) > 0) {
                BookList_swap(list, node2->prev, node2);
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
 * Search in a {@link BookList} by a filter.
 * @param list The {@link BookList} to be searched in.
 * @param filter A filter function for the search.
 * @param criteria The criteria data to be passed into
 *        {@param filter}.
 * @return A {@link BookList} containing the result.
 */
BookList *BookList_search(BookList *list,
        BOOL (*filter)(Book *book, void *criteria), void *criteria) {

    BookList *result = BookList_new();
    BookNode *node;

    BOOK_LIST_FOR_EACH(list, node) {
        if (filter(node->book, criteria)) {
            BookList_addEnd(result, node->book);
        }
    }

    return result;
}
