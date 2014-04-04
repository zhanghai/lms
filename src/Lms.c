/**
 * @file Lms.c
 * @author Zhang Hai
 */

#include "Lms.h"

#include "Library/ArrayList.h"
#include "Library/Console.h"


static string Lms_DATABASE_FILENAME = "lms.dat";

static string Lms_FUNCTIONS[] = {
        "Quit",
        "Search for books",
        "Add a book",
        "Modify books",
        "Remove books"};

static string Lms_CHOICES_YNQ[] = {"y", "n", "q"};


static void Lms_printTitle(string title);

static void Lms_printFunctions();

static void Lms_printBookFilters();

static void Lms_printBookFound();

static void Lms_promptBookNotFound();

static BookList *Lms_filterBook(BookList *list);

static string Lms_readBookString(string fieldName);

static void Lms_readBookStringArray(string array[], size_t size,
        string fieldName);

static bool Lms_readBookBoolean(string fieldName);

static bool Lms_modifyBookString(string *field, string fieldName);

static bool Lms_modifyBookStringArray(string (*array)[], size_t size,
        string fieldName);

static bool Lms_modifyBookBool(bool *field, string fieldName);


static void Lms_printTitle(string title) {
    Console_clear();
    Console_printSeparator();
    Console_printLine(title);
    Console_printSeparator();
}

static void Lms_printFunctions() {
    static size_t SIZE = array_size(Lms_FUNCTIONS);
    size_t i;
    for (i = 0; i < SIZE; ++i) {
        Console_printLine("[%zu] %s", i, Lms_FUNCTIONS[i]);
    }
}

static void Lms_printBookFilters() {
    size_t i;
    Console_printLine("Available book filters: ");
    Console_printLine("[%zu] %s", 0, "Full Text");
    for (i = 1; i < BOOK_FILTERS_SIZE; ++i) {
        Console_printLine("[%zu] %s", i, Book_FIELD_NAMES[i - 1]);
    }
}

static void Lms_printBookFound(size_t size) {
    Console_printLine("Found %zu book(s):", size);
}

static void Lms_promptBookNotFound() {
    Console_prompt("No book was found by specified filter(s).");
}

static BookList *Lms_filterBook(BookList *list) {

    static string INDEXES[] = {"0", "1", "2", "3", "4", "5", "6",
            "7"};

    size_t index;
    string keyword;
    BookFilter *filter, compoundFilter;
    ArrayList *filters = ArrayList_new();
    BookList *result;

    Lms_printBookFilters();
    do {
        index = Console_readChoice("Enter filter index", INDEXES,
                array_size(INDEXES));
        keyword = Console_readLine("Enter keyword: ");
        filter = Memory_allocateType(BookFilter);
        filter->filter = BOOK_FILTERS[index];
        filter->filterData = keyword;
        ArrayList_addEnd(filters, filter);
    } while (Console_readChoiceYN("Add another filter?"));

    compoundFilter.filter = BookFilters_compound;
    compoundFilter.filterData = filters;
    result = $(list, search, compoundFilter);

    ARRAY_LIST_FOR_EACH(filters, filter) {
        Memory_free(filter->filterData);
        Memory_free(filter);
    }
    ArrayList_delete(filters);

    return result;
}

static string Lms_readBookString(string fieldName) {
    Console_print(fieldName);
    return Console_readLine(": ");
}

/**
 * Read a string array from console, stopping if an empty string is
 * found, and the other elements will be filled by new empty strings.
 * @param array The string array to be filled.
 * @param size The size to be read;
 * @param fieldName The field name to be displayed.
 */
static void Lms_readBookStringArray(string array[], size_t size,
        string fieldName) {
    size_t i;
    bool fill = false;
    for (i = 0; i < size; ++i) {
        if (!fill) {
            Console_print("%s %zu: ", fieldName, i + 1);
            array[i] = Console_readLine("");
            if (string_isEmpty(array[i])) {
                fill = true;
            }
        } else {
            array[i] = string_clone(string_EMPTY);
        }
    }
}

static bool Lms_readBookBoolean(string fieldName) {
    return Console_readChoiceBoolean(fieldName);
}

static bool Lms_modifyBookString(string *field, string fieldName) {
    Console_print("Do you want to modify %s?", fieldName);
    switch (Console_readChoice("", Lms_CHOICES_YNQ,
            array_size(Lms_CHOICES_YNQ))) {
    case 0:
        Memory_free(*field);
        Console_print("Enter new %s: ", fieldName);
        *field = Console_readLine("");
        return true;
        break;
    case 1:
        return true;
        break;
    case 2:
        return false;
        break;
    default:
        Application_fatalError("Internal error at Lms_modifyBookString()");
        return false;
    }
}

/**
 * Modify a string array from console input, stopping if an empty
 * string is found, and the other elements will be replaced by new
 * empty strings if it is not.
 * @param array The pointer to the string array to be filled.
 * @param size The size to be read;
 * @param fieldName The field name to be displayed.
 */
static bool Lms_modifyBookStringArray(string (*array)[], size_t size,
        string fieldName) {
    size_t i;
    bool fill = false;
    for (i = 0; i < size; ++i) {
        if (!fill) {
            if (string_isEmpty((*array)[i])
                    && string_isEmpty((*array)[i - 1])) {
                return true;
            }
            Console_print("Do you want to modify %s %zu?", fieldName,
                    i + 1);
            switch (Console_readChoice("", Lms_CHOICES_YNQ,
                    array_size(Lms_CHOICES_YNQ))) {
            case 0:
                Memory_free((*array)[i]);
                Console_print("Enter new %s %zu: ", fieldName, i + 1);
                (*array)[i] = Console_readLine("");
                if (string_isEmpty((*array)[i])) {
                    fill = true;
                }
                break;
            case 1:
                break;
            case 2:
                return false;
                break;
            default:
                Application_fatalError("Internal error at Lms_modifyBookStringArray()");
                return false;
            }
        } else {
            if (!string_isEmpty((*array)[i])) {
                (*array)[i] = string_clone(string_EMPTY);
            }
        }
    }
    return true;
}

static bool Lms_modifyBookBool(bool *field, string fieldName) {
    Console_print("Do you want to modify %s?", fieldName);
    switch (Console_readChoice("", Lms_CHOICES_YNQ,
            array_size(Lms_CHOICES_YNQ))) {
    case 0:
        Console_print("Enter new %s: ", fieldName);
        *field = Console_readChoiceBoolean("");
                return true;
        break;
    case 1:
        return true;
        break;
    case 2:
        return false;
        break;
    default:
        Application_fatalError("Internal error at Lms_modifyBookBool()");
        return false;
    }
}

BookList *Lms_deserializeOrCreateBookList(string filename) {
    FILE *file;
    BookList *list;
    if ((file = fopen(filename, "rb")) == null) {
        if (errno == ENOENT) {
            // File not found, simply return a new BookList.
            return BookList_new();
        } else {
            // File already exists, but we failed to open it for reading.
            Application_fatalError("Opening database file for reading failed.");
            return null;
        }
    }
    list = BookList_deserialize(file);
    fclose(file);
    return list;
}

bool Lms_serializeBookList(BookList *list, string filename) {
    FILE *file;
    bool result;
    if ((file = fopen(filename, "wb")) == null) {
        Console_printErrorLine("Opening database file for writing failed.");
        return false;
    }
    result = BookList_serialize(list, file);
    fclose(file);
    return result;
}

void Lms_searchBook(BookList *list) {

    BookList *result;
    BookListNode *node;

    result = Lms_filterBook(list);

    Console_printSeparator();
    if (_(result, size) == 0) {
        Lms_promptBookNotFound();
    } else {
        Lms_printBookFound(_(result, size));
        BOOK_LIST_FOR_EACH(result, node) {
            Console_printSeparator();
            Book_print(node->book, stdout);
        }
        Console_printSeparator();
        Console_pause();
    }

    BookList_delete(result);
}

void Lms_addBook(BookList *list) {

    string title, authors[5], number, subjects[5], publisher, year;
    bool circulating;
    Book *book;

    title = Lms_readBookString(Book_FIELD_NAMES[0]);
    Lms_readBookStringArray(authors, 5, "Author");
    number = Lms_readBookString(Book_FIELD_NAMES[2]);
    Lms_readBookStringArray(subjects, 5, "Subject");
    publisher = Lms_readBookString(Book_FIELD_NAMES[4]);
    year = Lms_readBookString(Book_FIELD_NAMES[5]);
    circulating = Lms_readBookBoolean(Book_FIELD_NAMES[6]);

    book = Book_new(title, authors, number, subjects, publisher, year,
            circulating);
    $(list, addEnd, book);
    Book_removeReference(book);
    Console_printSeparator();
    Console_prompt("Book added successfully.");
}

void Lms_modifyBook(BookList *list) {

    BookList *result;
    BookListNode *node;
    Book *book;
    bool quit = false;

    result = Lms_filterBook(list);

    Console_printSeparator();
    if (_(result, size) == 0) {
        Lms_promptBookNotFound();
    } else {
        Lms_printBookFound(_(result, size));
        BOOK_LIST_FOR_EACH(result, node) {
            book = node->book;
            Console_printSeparator();
            Book_print(book, stdout);
            Console_printSeparator();
            switch (Console_readChoice(
                    "Do you want to modify this book?",
                    Lms_CHOICES_YNQ, array_size(Lms_CHOICES_YNQ))) {
            case 0:
                if (Lms_modifyBookString(&book->title,
                        Book_FIELD_NAMES[0])) {
                    // HACK: Use the boolean result with an empty if.
                    if (Lms_modifyBookStringArray(&book->authors, 5,
                            "Author")
                    && Lms_modifyBookString(&book->number,
                            Book_FIELD_NAMES[2])
                    && Lms_modifyBookStringArray(&book->subjects, 5, "Subject")
                    && Lms_modifyBookString(&book->publisher,
                            Book_FIELD_NAMES[4])
                    && Lms_modifyBookString(&book->year,
                            Book_FIELD_NAMES[5])
                    && Lms_modifyBookBool(&book->circulating,
                            Book_FIELD_NAMES[6])) {}
                    Console_printSeparator();
                    Console_prompt("Book modified successfully.");
                }
                break;
            case 1:
                break;
            case 2:
                quit = true;
                break;
            default:
                Application_fatalError("Internal error at Lms_modifyBook()");
                return;
            }
            if (quit) {
                break;
            }
        }
    }

    BookList_delete(result);
}

void Lms_removeBook(BookList *list) {

    BookList *result;
    BookListNode *node;

    result = Lms_filterBook(list);

    Console_printSeparator();
    if (_(result, size) == 0) {
        Lms_promptBookNotFound();
    } else {
        Lms_printBookFound(_(result, size));
        BOOK_LIST_FOR_EACH(result, node) {
            Console_printSeparator();
            Book_print(node->book, stdout);
            Console_printSeparator();
            if (Console_readChoiceYN("Do you want to remove this book? ")) {
                $(list, remove, node->book);
                Console_printSeparator();
                Console_prompt("Book removed successfully.");
            }
        }
    }

    BookList_delete(result);
}

void Lms_loop() {

    static string FUNCTION_CHOICES[] = {"0", "1", "2", "3", "4"};

    BookList *list;
    size_t choice;
    bool quit = false;

    if ((list = Lms_deserializeOrCreateBookList(Lms_DATABASE_FILENAME)) == NULL) {
        Application_fatalError("Reading database from file failed.");
    }

    do {
        Lms_printTitle("Library Management System");
        Lms_printFunctions();
        choice = Console_readChoice("Please select a function",
                FUNCTION_CHOICES, array_size(FUNCTION_CHOICES));
        Lms_printTitle(Lms_FUNCTIONS[choice]);
        switch (choice) {
        case 0:
            quit = true;
            break;
        case 1:
            Lms_searchBook(list);
            break;
        case 2:
            Lms_addBook(list);
            break;
        case 3:
            Lms_modifyBook(list);
            break;
        case 4:
            Lms_removeBook(list);
            break;
        default:
            Application_fatalError("Internal error at Lms_modifyBookString()");
        }
    } while (!quit);

    if (!Lms_serializeBookList(list, Lms_DATABASE_FILENAME)) {
        Console_printErrorLine("Writing database to file failed.");
    }
}
