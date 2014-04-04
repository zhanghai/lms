/**
 * @file BookList.c
 * @author Zhang Hai
 */

#include "BookList.h"


void BookList_initialize(BookList *this) {

    LinkedList_initialize((LinkedList *)this);

    _$(this, new) = BookList_new;
    _$(this, delete) = BookList_delete;
    _$(this, newNode) = BookList_newNode;
    _$(this, deleteNode) = BookList_deleteNode;
}

void BookList_finalize(BookList *this) {
    LinkedList_finalize((LinkedList *)this);
}

OBJECT_DEFINE_NEW(BookList, BookList_Fields, BookList_Methods)

OBJECT_DEFINE_DELETE(BookList)

BookListNode *BookList_newNode(Book *book, BookListNode *previous,
        BookListNode *next) {
    Book_addReference(book);
    return (BookListNode *) LinkedList_newNode(book,
            (LinkedListNode *)previous, (LinkedListNode *)next);
}

void BookList_deleteNode(BookListNode *node) {
    LinkedList_deleteNode((LinkedListNode *)node);
    Book_removeReference(node->book);
}

/**
 * Serialize a {@link BookList} to file.
 * @param list The {@link BookList} to be serialized.
 * @param file The file to serialize the list.
 * @return Whether the serialization was successful.
 */
bool BookList_serialize(BookList *list, FILE *file) {

    BookListNode *node;

    size_t_serialize(&_(list, size), file);
    LINKED_LIST_FOR_EACH(list, node) {
        if (!Book_serialize(node->book, file)) {
            return false;
        }
    }

    return true;
}

/**
 * Deserialize a {@link BookList} from file.
 * @param file The file to deserialize a {@link BookList} from.
 * @return a {@link BookList} deserialized from the file, or null
 *         if failed to read sufficient book.
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
        $(list, addEnd, book);
        Book_removeReference(book);
    }

    return list;
}
