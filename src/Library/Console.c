/*
 * File: Console.c
 * Author: Zhang Hai
 */

#include "Console.h"

#include <stdarg.h>
#include <readline/readline.h>
#include <readline/history.h>


static string CONSOLE_CHOICES_Y_N[] = {"y", "n"};

static string CONSOLE_CHOICES_BOOLEAN[] = {"True", "False"};

void Console_print(string format, ...) {
    va_list arguments;
    va_start(arguments, format);
    vprintf(format, arguments);
    va_end(arguments);
}

void Console_printLine(string format, ...) {
    va_list arguments;
    va_start(arguments, format);
    vprintf(format, arguments);
    va_end(arguments);
    printf("\n");
}

void Console_printSeparator() {
    Console_printLine("----------------------------------------");
}

void Console_prompt(string message) {
    Console_printLine(message);
    Console_pause();
}

void Console_printError(string format, ...) {
    va_list arguments;
    va_start(arguments, format);
    vfprintf(stderr, format, arguments);
    va_end(arguments);
}

void Console_printErrorLine(string format, ...) {
    va_list arguments;
    va_start(arguments, format);
    vfprintf(stderr, format, arguments);
    va_end(arguments);
    fprintf(stderr, "\n");
}

string Console_readLine(string message) {
    string line;
    while ((line = readline(message)) == null);
    if (!string_isEmpty(line)) {
        add_history(line);
    }
    return line;
}

size_t Console_readChoice(string message, string choices[],
        size_t choicesSize) {

    string line;
    size_t index;

    while (true) {
        Console_print("%s [", message);
        string_array_print(choices, choicesSize, "/", stdout);
        line = Console_readLine("]: ");
        index = string_array_containsEqualIgnoreCase(choices,
                choicesSize, line);
        if (index != -1){
            Memory_free(line);
            break;
        }
        Console_printLine("Invalid choice \"%s\".", line);
        Memory_free(line);
    }

    return index;
}

bool Console_readChoiceYN(string message) {
    return Console_readChoice(message, CONSOLE_CHOICES_Y_N,
            sizeof(CONSOLE_CHOICES_Y_N) / sizeof(CONSOLE_CHOICES_Y_N[0])) == 0;
}

bool Console_readChoiceBoolean(string message) {
    return Console_readChoice(message, CONSOLE_CHOICES_BOOLEAN,
            sizeof(CONSOLE_CHOICES_BOOLEAN) / sizeof(CONSOLE_CHOICES_BOOLEAN[0])) == 0;
}

void Console_pause() {
    Memory_free(Console_readLine("Press <Enter> to continue..."));
}

void Console_clear() {
#ifdef _WIN32
    system("cls");
#else // POSIX
    system("clear");
#endif
}
