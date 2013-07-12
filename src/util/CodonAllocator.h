// Jacob Cole
// Created July 2013

#ifndef CODON_ALLOCATOR_H
#define CODON_ALLOCATOR_H

typedef struct CodonAllocatorValue {
	char allocated;
	void* value;
} CodonAllocatorValue;

typedef struct CodonAllocator {
	int capacity;
	int minFreeIndex;
	int maxAllocatedIndex;

	CodonAllocatorValue* data;
} CodonAllocator;

// ============================================================================
// initialize an empty allocator
void CodonAllocator_init(CodonAllocator* self, int initialCapacity);
// free resources used by allocator, will not free data pointed to
void CodonAllocator_free(CodonAllocator* self);

// ----------------------------------------------------------------------------
// returns true if the given index is allocated or not
char CodonAllocator_isAllocated(CodonAllocator* self, int index);
// returns the first allocated index for the allocator, -1 if no index
int CodonAllocator_firstAllocatedIndex(CodonAllocator* self);
// returns the next index that is allocated after the given index
// -1 if no index allocated after
int CodonAllocator_nextAllocatedIndex(CodonAllocator* self, int index);

// ----------------------------------------------------------------------------
// get the pointer stored at the given index
void* CodonAllocator_get(CodonAllocator* self, int index);
// set the pointer stored at the given index
void CodonAllocator_set(CodonAllocator* self, int index, void* value);

// ----------------------------------------------------------------------------
// allocate a new pointer, the index of the pointer is returned
int CodonAllocator_allocate(CodonAllocator* self);
// deallocate the pointer at the given index, this will not free and additional
// resources pointed to by the 
void CodonAllocator_release(CodonAllocator* self, int index);

#endif
