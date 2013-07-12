// Jacob Cole
// Created June 2013

// This module handles memory allocation for the StackCodon interpreter

#ifndef CODON_MEMORY_ALLOCATOR_H
#define CODON_MEMORY_ALLOCATOR_H

#include "CodonStack.h"
#include "CodonAllocator.h"

// A stack entry in the memory allocator keeps track of the stack data as well
// as the number of references to it (freed when refereces are reduced to 0)
typedef struct CodonMemoryAllocatorStack {
    // the number of references to this stack
    int referenceCount;
    // reference to a stack, null if not allocated
    CodonStack stack;
} CodonMemoryAllocatorStack;

typedef struct CodonMemoryAllocator {
	CodonAllocator allocator;
} CodonMemoryAllocator;

// allocate and initialize a new CodonMemoryAllocator
CodonMemoryAllocator* CodonMemoryAllocator_new(int initialCapacity);
// delete this CodonMemoryAllocator, all stack memory will be freed
void CodonMemoryAllocator_delete(CodonMemoryAllocator* self);

// allocate a new stack, return it's index, stack will have a refcount of 1
int CodonMemoryAllocator_allocate(CodonMemoryAllocator* self);
// retain a stack reference, its reference count will be incremented
void CodonMemoryAllocator_retain(CodonMemoryAllocator* self, int index);
// release a stack reference, its reference count will be decremented, if the
// count is reduced to 0 the stack will be freed
void CodonMemoryAllocator_release(CodonMemoryAllocator* self, int index);

// retrieve the stack that corresponds to that index
// NULL if no corresponding index
CodonStack* CodonMemoryAllocator_get(CodonMemoryAllocator* self, int index);

#endif
