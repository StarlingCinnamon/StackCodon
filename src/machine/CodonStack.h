// Jacob Cole
// Created June 2013

// This represents a stack that may be pushed or popped from.
#ifndef CODON_STACK_H
#define CODON_STACK_H

#include <stdlib.h>

typedef struct CodonStack {
    // the total size of the stack
    int count;

    // the length of this segment of the stack
    int capacity;
    // the current index of the stack head
    int stackHeadIndex;
    // data array for the stack
    double* data;
} CodonStack;

// ============================================================================
// initialize a new codonstack with the given initial capacity
void CodonStack_init(CodonStack*self, int initialCapacity);
// allocating init
CodonStack* CodonStack_new(int initialCapacity);

// delete a CodonStack
void CodonStack_free(CodonStack* self);
// freeing version
void CodonStack_delete(CodonStack* self);

// ----------------------------------------------------------------------------
// get the number of elements on this stack
int CodonStack_size(CodonStack* self);

// ----------------------------------------------------------------------------
// push a single value onto the given stack
void CodonStack_push(CodonStack* self, double value);
// pop a single value from the given stack
double CodonStack_pop(CodonStack* self);
// return the value at the top of the stack
double CodonStack_peek(CodonStack* self);

#endif
