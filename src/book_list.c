/*
 * File: book_list.c
 * Author: Zhang Hai
 */

#include "book_list.h"


static BookNode *book_node_new(Book *book, BookNode *prev,
        BookNode *next);
static void book_node_delete(BookNode *node);


static BookNode *book_node_new(Book *book, BookNode *prev,
        BookNode *next) {

    BookNode *node = LMS_NEW(BookNode);

    book_add_reference(book);
    node->book = book;
    node->prev = prev;
    node->next = next;

    return node;
}

static void book_node_delete(BookNode *node) {

    book_remove_reference(node->book);

    free(node);
}

/**
 * Create a new instance of {@link BookList}.
 * @return The created {@link BookList} instance.
 */
BookList *book_list_new() {

    BookList *list = LMS_NEW(BookList);

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

/**
 * Destroy a {@link Book} instance.
 * @param list The {@link BookList} instance to be destroyed.
 */
void book_list_delete(BookList *list) {

    BookNode *node;
    BOOK_LIST_FOR_EACH(list, node) {
        book_node_delete(node);
    }

    free(list);
}

/**
 * Serialize a {@link BookList} to file.
 * @param list The {@link BookList} to be serialized.
 * @param file The file to serialize {@param list}.
 * @return Whether the serialization was successful.
 */
BOOL book_list_serialize(BookList *list, FILE *file) {
    BookNode *node;
    serialize_size(&list->size, file);
    BOOK_LIST_FOR_EACH(list, node) {
        if (!book_serialize(node->book, file)) {
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
BookList *book_list_deserialize(FILE *file) {

    BookList *list = book_list_new();
    size_t size, i;
    Book *book;

    if (!deserialize_size(&size, file)) {
        return NULL;
    }
    for (i = 0; i < size; ++i) {
        if ((book = book_deserialize(file)) == NULL) {
            return NULL;
        }
        book_list_add_end(list, book);
    }

    return list;
}

/**
 * Add a {@link Book} instance to the start of a {@link BookList}.
 * @param list The {@link BookList} to add {@param book} to.
 * @param book The {@link Book} to be added.
 * @return The newly added node in the {@param list}.
 */
BookNode *book_list_add_start(BookList *list, Book *book) {

    BookNode *node = book_node_new(book, NULL,
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
BookNode *book_list_add_end(BookList *list, Book *book) {

    BookNode *node = book_node_new(book, list->tail, NULL);

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
 * Insert a new node holding @param{book} before {@param node}.
 * @param list The {@link BookList} to insert {@param book} into.
 * @param node The node to insert before.
 * @param book The {@link Book} to be inserted.
 * @return The new node just inserted.
 */
BookNode *book_list_insert_before(BookList *list, BookNode *node,
        Book *book) {

    BookNode *new_node = book_node_new(book, node->prev, node);

    if (node->prev != NULL) {
        node->prev->next = new_node;
    } else {
        list->head = new_node;
    }
    node->prev = new_node;

    ++list->size;

    return new_node;
}

/**
 * Insert a new node holding @param{book} after {@param node}.
 * @param list The {@link BookList} to insert {@param book} into.
 * @param node The node to insert after.
 * @param book The {@link Book} to be inserted.
 * @return The new node just inserted.
 */
BookNode *book_list_insert_after(BookList *list, BookNode *node,
        Book *book) {

    BookNode *new_node = book_node_new(book, node, node->next);

    if (node->next != NULL) {
        node->next->prev = new_node;
    } else {
        list->tail = new_node;
    }
    node->next = new_node;

    ++list->size;

    return new_node;
}

/**
 * Remove {@param node} from a {@link BookList}.
 * @param list The {@link BookList} to remove the node from.
 * @param node The node to be removed.
 * @return the node following the removed one, or NULL if the tail
 *         node is removed.
 */
BookNode *book_list_remove_node(BookList *list, BookNode *node) {

    BookNode *next_node = node->next;

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

    book_node_delete(node);

    --list->size;

    return next_node;
}

/**
 * Remove a {@link Book} instance from a {@link BookList}.
 * @param list The {@link BookList} to remove {@param book} from.
 * @param book The {@link Book} instance to be removed.
 */
void book_list_remove(BookList *list, Book *book) {
    BookNode *node;
    BOOK_LIST_FOR_EACH(list, node) {
        if (node->book == book) {
            book_list_remove_node(list, node);
            return;
        }
    }
}

/**
 * Swap two nodes in a {@link BookList}.
 * Will simply swap the {@link Book} objects of the two nodes.
 * @param node1 The first node to be swapped.
 * @param node2 The second node to be swapped.
 */
void book_list_swap(BookList *list, BookNode *node1,
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
void book_list_sort(BookList *list,
        int (*comparator)(BookNode *node1, BookNode *node2)) {

    BookNode *node1, *node2;
    BOOL changed;

    if (list->size == 0) {
        return;
    }

    for (node1 = list->head; node1->next != NULL;
            node1 = node1->next) {

        changed = FALSE;

        for (node2 = list->tail; node2 != node1; ) {
            if (comparator(node2->prev, node2) > 0) {
                book_list_swap(list, node2->prev, node2);
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
 * Search in a {@link BookList} according to a filter.
 * @param list The {@link BookList} to be searched in.
 * @param filter A filter function for the search.
 * @param criteria The criteria data to be passed into
 *        {@param filter}.
 * @return A {@link BookList} containing the result.
 */
BookList *book_list_search(BookList *list,
        BOOL (*filter)(Book *book, void *criteria), void *criteria) {

    BookList *result = book_list_new();
    BookNode *node;

    BOOK_LIST_FOR_EACH(list, node) {
        if (filter(node->book, criteria)) {
            book_list_add_end(result, node->book);
        }
    }

    return result;
}

/*
int book_node_cmp_z_order(BookNode *node1, BookNode *node2) {
    int z_order1 = node1->book->z_order,
            z_order2 = node2->book->z_order;
    return z_order1 < z_order2 ? -1 : (z_order1 == z_order2 ? 0 : 1);
}
*/
