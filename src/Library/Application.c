/**
 * @file Application.c
 * @author Zhang Hai
 */

#include "Application.h"

#include <stdio.h>
#include <stdlib.h>

void Application_exit(int status) {
    exit(status);
}

void Application_fatalError(string message) {
    fprintf(stderr, "Fatal error: %s\n", message);
    Application_exit(1);
}
