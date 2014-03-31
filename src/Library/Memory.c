/*
 * File: Memory.c
 * Author: Zhang Hai
 */

#include "Memory.h"

#include <stdlib.h>

#include "Application.h"


static void Memory_checkAllocation(void *address) {
    if (address == null) {
        Application_fatalError("Memory allocation failed.");
    }
}


/**
 * Allocate memory of {@param size} bytes.
 * @note This function will clear the allocated memory to 0.
 * @param size The size of the memory to be allocated.
 */
void *Memory_allocate(size_t size) {
    void *address = calloc(1, size);
    Memory_checkAllocation(address);
    return address;
}

/**
 * Reallocate memory at {@param address} to {@param size} bytes.
 * @note This function will NOT clear the reallocated memory.
 * @param address The address of the memory.
 * @param size The size of the memory to be reallocated to.
 */
void *Memory_reallocate(void *address, size_t size) {
    address = realloc(address, size);
    Memory_checkAllocation(address);
    return address;
}

void Memory_free(void *address) {
    free(address);
}
