/*
 * File: Console.c
 * Author: Zhang Hai
 */

#include "Console.h"

#include <stdarg.h>
#include <readline/readline.h>
#include <readline/history.h>


string CONSOLE_CHOICES_Y_N[] = {"y", "n"};


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
    if (string_length(line) > 0) {
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
        string_array_print(stdout, choices, choicesSize, "/");
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

bool Console_readYN(string message) {
    return Console_readChoice(message, CONSOLE_CHOICES_Y_N,
            sizeof(CONSOLE_CHOICES_Y_N) / sizeof(CONSOLE_CHOICES_Y_N[0]))
            == 0;
}
