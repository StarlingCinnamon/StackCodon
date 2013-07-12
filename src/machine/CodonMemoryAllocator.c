#include "CodonMemoryAllocator.h"

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

// ============================================================================
CodonMemoryAllocator* CodonMemoryAllocator_new(int initialCapacity) {
    CodonMemoryAllocator* self = malloc(sizeof(CodonMemoryAllocator));

	CodonAllocator_init(&(self->allocator), 2);

    return self;
}

void CodonMemoryAllocator_delete(CodonMemoryAllocator* self) {
	// iterate through the stacks, freeing the associated memory
    int index = CodonAllocator_firstAllocatedIndex(&(self->allocator));
	while (index > 0) {
		CodonMemoryAllocatorStack* stack = (CodonMemoryAllocatorStack*)CodonAllocator_get(&(self->allocator), index);
		CodonStack_free(&(stack->stack));
		free(stack);

		index = CodonAllocator_nextAllocatedIndex(&(self->allocator), index);
	}
    free(self);
}

int CodonMemoryAllocator_allocate(CodonMemoryAllocator* self) {
	// allocate a new index
	int index = CodonAllocator_allocate(&(self->allocator));

    // allocate the new stack
	CodonMemoryAllocatorStack* memStack = malloc(sizeof(CodonMemoryAllocatorStack));
    memStack->referenceCount = 1/*a single reference*/;
    CodonStack_init(&(memStack->stack), 2);

	// store the new stack on the index
	CodonAllocator_set(&(self->allocator), index, memStack);

	// return the index for further reference
    return index;
}

void CodonMemoryAllocator_retain(CodonMemoryAllocator* self, int index) {
	// if the given index is allocated, then increment the stack at the index
	if (CodonAllocator_isAllocated(&(self->allocator), index))
		((CodonMemoryAllocatorStack*)CodonAllocator_get(&(self->allocator), index))->referenceCount++;
}

void CodonMemoryAllocator_release(CodonMemoryAllocator* self, int index) {
	if (CodonAllocator_isAllocated(&(self->allocator), index)) {
		// obtain a reference to the allocator stack
		CodonMemoryAllocatorStack* memStack = CodonAllocator_get(&(self->allocator), index);

		// decrement the reference count
		memStack->referenceCount--;

		// free the stack if there are no references left
		if (memStack->referenceCount <= 0) {
			// free up memory taken by stack
			CodonStack_free(&(memStack->stack));
			free(memStack);

			// release the allocator slot
			CodonAllocator_release(&(self->allocator), index);
		}
	}
}

CodonStack* CodonMemoryAllocator_get(CodonMemoryAllocator* self, int index) {
	// if the given index is allocated then return a pointer to the stack, if the
	// index is not allocated, return NULL
    if (CodonAllocator_isAllocated(&(self->allocator), index))
        return &(((CodonMemoryAllocatorStack*)CodonAllocator_get(&(self->allocator), index))->stack);
	else
		return NULL;
}
