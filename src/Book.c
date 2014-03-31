/*
 * File: Book.c
 * Author: Zhang Hai
 */

#include "Book.h"


string Book_FIELD_NAMES[] = {
    "Title",
    "Author(s)",
    "LOC Catalog Number",
    "Publisher",
    "Subject(s)",
    "Year",
    "Circulating"
};


static void Book_delete(Book *book);


/**
 * Create a new instance of {@link Book}.
 * The constructor will make copies of the strings passed in.
 * The initial reference count will be set to 1.
 * @note You should always call {@link Book_removeReference} before
 *       the end of your function where you called this function.
 * @param title The title of the book.
 * @param authors The authors of this book.
 * @param number The LOC catalog number of this book.
 * @param subjects The subject headings of this book.
 * @param publisher The publisher of this book.
 * @param year The year when this book is published.
 * @param circulating Whether this book is still circulating.
 * @return The created {@link Book} instance.
 */
Book *Book_new(string title, string authors[5], string number,
        string subjects[5], string publisher, string year,
        bool circulating) {

    Book *book = Memory_allocateType(Book);

    book->reference_count = 1;
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
 * @private
 * Destroy a {@link Book} instance.
 * @note This function is only intended for internal use, developers
 *       should use {@link Book_removeReference} instead.
 * @param book The {@link Book} instance to be destroyed.
 */
static void Book_delete(Book *book) {

    Memory_free(book->title);
    string_array_free(book->authors, 5);
    Memory_free(book->number);
    string_array_free(book->subjects, 5);
    Memory_free(book->publisher);
    Memory_free(book->year);

    Memory_free(book);
}

/**
 * Add a reference to a {@link Book} instance.
 * @param book The {@link Book} instance to add a reference to.
 */
void Book_addReference(Book *book) {
    ++book->reference_count;
}

/**
 * Remove a reference to a {@link Book} instance, will delete the
 * instance if reference count reaches 0.
 * @param book The {@link Book} instance to remove a reference from.
 */
void Book_removeReference(Book *book) {
    if(--book->reference_count == 0) {
        Book_delete(book);
    }
}

/**
 * Serialize a {@link Book} to file.
 * @param book The {@link Book} to be serialized.
 * @param file The file to serialize {@param book}.
 * @return Whether the serialization was successful.
 */
bool Book_serialize(Book *book, FILE *file) {
    return string_serialize(book->title, file)
            && string_array_serialize(book->authors, 5, file)
            && string_serialize(book->number, file)
            && string_array_serialize(book->subjects, 5, file)
            && string_serialize(book->publisher, file)
            && string_serialize(book->year, file)
            && bool_serialize(&book->circulating, file);
}

/**
 * Deserialize a {@link Book} from file.
 * @param file The file to deserialize a {@link Book} from.
 * @return A {@link Book} deserialized from {@param file}, or null if
 *         an error occurred.
 */
Book *Book_deserialize(FILE *file) {
    Book *book = Memory_allocateType(Book);
    if (string_deserialize(&book->title, file)
            && string_array_deserialize(book->authors, 5, file)
            && string_deserialize(&book->number, file)
            && string_array_deserialize(book->subjects, 5, file)
            && string_deserialize(&book->publisher, file)
            && string_deserialize(&book->year, file)
            && bool_deserialize(&book->circulating, file)) {
        book->reference_count = 1;
        return book;
    } else {
        Book_delete(book);
        return null;
    }
}

/**
 * @deprecated Use {@link Book_addReference} instead.
 * Clone a {@link Book} instance.
 * @param book The {@link Book} instance to clone.
 * @return The cloned {@link Book} instance.
 */
Book *Book_clone(Book *book) {
    return Book_new(book->title, book->authors, book->number,
            book->subjects, book->publisher, book->year,
            book->circulating);
}

/**
 * @deprecated In most cases you may want to compare the two pointers
 *             directly.
 * Check if two {@link Book} instances are equal.
 * @param book1 The first {@link Book} instance.
 * @param book2 The second {@link Book} instance.
 * @return Whether the two {@link Book} instances are equal.
 */
bool Book_isEqual(Book *book1, Book *book2) {
    return string_isEqual(book1->title, book2->title)
            && string_array_isEqual(book1->authors, book2->authors, 5)
            && string_isEqual(book1->number, book2->number)
            && string_array_isEqual(book1->subjects, book2->subjects, 5)
            && string_isEqual(book1->publisher, book2->publisher)
            && string_isEqual(book1->year, book2->year)
            && book1->circulating == book2->circulating;
}

/**
 * Print the information stored in a {@link Book} instance.
 * @param book The {@link Book} instance to print.
 */
void Book_print(FILE *file, Book *book) {
    fprintf(file, "%-18s: %s\n", Book_FIELD_NAMES[0], book->title);
    fprintf(file, "%-18s: ", Book_FIELD_NAMES[1]);
    string_array_print(file, book->authors, 5, "; ");
    fprintf(file, "\n");
    fprintf(file, "%-18s: %s\n", Book_FIELD_NAMES[2], book->number);
    fprintf(file, "%-18s: ", Book_FIELD_NAMES[3]);
    string_array_print(file, book->subjects, 5, "; ");
    fprintf(file, "\n");
    fprintf(file, "%-18s: %s\n", Book_FIELD_NAMES[4],
            book->publisher);
    fprintf(file, "%-18s: %s\n", Book_FIELD_NAMES[5], book->year);
    fprintf(file, "%-18s: ", Book_FIELD_NAMES[6]);
    bool_print(file, book->circulating);
    fprintf(file, "\n");
}