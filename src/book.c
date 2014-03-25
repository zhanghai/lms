/*
 * File: book.c
 * Author: Zhang Hai
 */

#include "book.h"


/**
 * Create a new instance of {@link Book}.
 * The constructor will make copies of the strings passed in.
 * @param title
 * @param authors
 * @param number
 * @param subjects
 * @param publisher
 * @param year
 * @param circulating
 * @return The created {@link Book} instance.
 */
Book *book_new(char *title, char *authors[5], char *number,
        char *subjects[5], char *publisher, char *year,
        BOOL circulating) {

    Book *book = LMS_NEW(Book);

    book->title = string_clone(title);
    string_array_clone(authors, book->authors, 5);
    book->number = string_clone(number);
    string_array_clone(subjects, book->subjects, 5);
    book->publisher = string_clone(publisher);
    book->year = string_clone(year);
    book->circulating = circulating;

    return book;
}

/**
 * Destroy a {@link Book} instance.
 * @param book The {@link Book} instance to be destroyed.
 */
void book_delete(Book *book) {

    free(book->title);
    string_array_free(book->authors, 5);
    free(book->number);
    string_array_free(book->subjects, 5);
    free(book->publisher);
    free(book->year);

    free(book);
}

/**
 * Serialize a {@link Book} to file.
 * @param book The {@link Book} to be serialized.
 * @param file The file to serialize {@param book}.
 * @return Whether the serialization was successful.
 */
BOOL book_serialize(Book *book, FILE *file) {
    return serialize_string(book->title, file)
            && serialize_string_array(book->authors, 5, file)
            && serialize_string(book->number, file)
            && serialize_string_array(book->subjects, 5, file)
            && serialize_string(book->publisher, file)
            && serialize_string(book->year, file)
            && serialize_bool(&book->circulating, file);
}

/**
 * Deserialize a {@link Book} from file.
 * @param file The file to deserialize a {@link Book} from.
 * @return a {@link Book} deserialized from {@param file}, or NULL if
 *         an error occurred.
 */
Book *book_deserialize(FILE *file) {
    Book *book = LMS_NEW(Book);
    if (deserialize_string(&book->title, file)
            && deserialize_string_array(book->authors, 5, file)
            && deserialize_string(&book->number, file)
            && deserialize_string_array(book->subjects, 5, file)
            && deserialize_string(&book->publisher, file)
            && deserialize_string(&book->year, file)
            && deserialize_bool(&book->circulating, file)) {
        return book;
    } else {
        book_delete(book);
        return NULL;
    }
}

Book *book_clone(Book *book) {
    return book_new(book->title, book->authors, book->number,
            book->subjects, book->publisher, book->year,
            book->circulating);
}

BOOL *book_is_equal(Book *book1, Book *book2) {
    return strcmp(book1->title, book2->title) == 0
            && string_array_is_equal(book1->authors, book2->authors, 5)
            && strcmp(book1->number, book2->number)
            && string_array_is_equal(book1->subjects, book2->subjects, 5)
            && strcmp(book1->publisher, book2->publisher)
            && strcmp(book1->year, book2->year)
            && book1->circulating == book2->circulating;
}

void book_print(Book *book) {
    printf("Title:              %s\n", book->title);
    printf("Author(s):          ");
    string_array_print(book->authors, 5);
    printf("\n");
    printf("LoC catalog number: %s\n", book->number);
    printf("Subject(s):         ");
    string_array_print(book->subjects, 5);
    printf("\n");
    printf("Publisher:          %s\n", book->publisher);
    printf("Year:               %s\n", book->year);
    printf("Circulating:        ");
    bool_print(book->circulating);
    printf("\n");
}
