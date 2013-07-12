#include "CodonStack.h"

#include "CodonArrayUtil.h"

#include <stdio.h>

// ****************************************************************************
#define STACK_SIZE_MULTIPLIER 2

inline double* resizeStack(double* data, int count, int capacity) {
    return resizeArray(data, count*sizeof(double), capacity*sizeof(double));
}

// ****************************************************************************
void CodonStack_init(CodonStack* self, int initialCapacity) {
    self->count = 0;
    self->capacity = initialCapacity;
    self->data = malloc(self->capacity * sizeof(double));
}
CodonStack* CodonStack_new(int initialCapacity) {
    CodonStack* self = malloc(sizeof(CodonStack));

	CodonStack_init(self, initialCapacity);

    return self;
}

void CodonStack_free(CodonStack* self) {
	free(self->data);
}
void CodonStack_delete(CodonStack* self) {
	CodonStack_free(self);
    free(self);
}

// ============================================================================
int CodonStack_size(CodonStack* self) {
	return self->count;
}

// ============================================================================
void CodonStack_push(CodonStack* self, double value) {
    // expand the size of the stack array if needed
    if (self->count >= self->capacity) {
        // expand the capacity
        self->capacity *= STACK_SIZE_MULTIPLIER;
        self->data = resizeStack(self->data, self->count, self->capacity);
    }

    // push the value
    self->count++;
    self->data[self->count - 1] = value;
}

double CodonStack_pop(CodonStack* self) {
    // pop the value, default to 0.0 if there is nothing to pop
    double result;
    if (self->count == 0) {
        result = 0.0;
    } else {
        self->count--;
        result = self->data[self->count];
    }

    // shrink the capacity if the count is less than two 'steps' below the capacity
    if (self->capacity >= STACK_SIZE_MULTIPLIER && self->capacity > self->count * STACK_SIZE_MULTIPLIER * STACK_SIZE_MULTIPLIER) {
        // shrink the capacity
        self->capacity /= STACK_SIZE_MULTIPLIER;
        self->data = resizeStack(self->data, self->count, self->capacity);
    }

    return result;
}

double CodonStack_peek(CodonStack* self) {
    if (self->count == 0) {
        return 0.0;
    } else {
        return self->data[self->count];
    }
}


