// Jacob Cole
// Created July 2013

#include "CodonAllocator.h"

#include <stdlib.h>

#include "CodonArrayUtil.h"

const int CAPACITY_MULTIPLIER = 2;

void resizeData(CodonAllocator* self, int newCapacity) {
	// set the new capacity and copy the data
	self->capacity = newCapacity;
	int maxCopied = self->maxAllocatedIndex+1;
	self->data = resizeArray(self->data, maxCopied*sizeof(CodonAllocatorValue), self->capacity*sizeof(CodonAllocatorValue));
	
	// initialize the remainder of the data slots to be unallocated
	int i;
	for (i = maxCopied; i < self->capacity; i++) {
		self->data[i].allocated = 0;
		self->data[i].value = NULL;
	}
}

// ****************************************************************************
// initialize an empty allocator
void CodonAllocator_init(CodonAllocator* self, int initialCapacity) {
	self->capacity = initialCapacity;
	self->minFreeIndex = 0;
	self->maxAllocatedIndex = -1;

	self->data = malloc(self->capacity * sizeof(CodonAllocatorValue));
	int i;
	for (i = 0; i < self->capacity; i++) {
		self->data[i].allocated = 0;
		self->data[i].value = NULL;
	}
}
// free resources used by allocator, will not free data pointed to
void CodonAllocator_free(CodonAllocator* self) {
	free(self->data);
}

// ============================================================================
// returns true if the given index is allocated or not
char CodonAllocator_isAllocated(CodonAllocator* self, int index) {
	if (index < 0 || index >= self->capacity)
		return 0;
	
	return self->data[index].allocated;
}
// returns the first allocated index for the allocator, -1 if nothing allocated
int CodonAllocator_firstAllocatedIndex(CodonAllocator* self) {
	int i;
	for (i = 0; i < self->capacity; i++) {
		if (self->data[i].allocated)
			return i;
	}
	return -1;
}
// returns the next index that is allocated after the given index
// -1 if no index allocated after
int CodonAllocator_nextAllocatedIndex(CodonAllocator* self, int index) {
	index++;
	for (; index < self->capacity; index ++) {
		if (self->data[index].allocated)
			return index;
	}
	return -1;
}

// ============================================================================
// get the pointer stored at the given index
void* CodonAllocator_get(CodonAllocator* self, int index) {
	if (index < 0 || index >= self->capacity)
		return NULL;

	return self->data[index].value;
}
// set the pointer stored at the given index
void CodonAllocator_set(CodonAllocator* self, int index, void* value) {
	if (!(index < 0 || index >= self ->capacity || !self->data[index].allocated))
		self->data[index].value = value;
}

// ============================================================================
// allocate a new pointer, the index of the pointer is returned
int CodonAllocator_allocate(CodonAllocator* self) {
	// find the first unallocated index
	int i, index = -1;
	for (i = self->minFreeIndex; i < self->capacity; i++) {
		if (!self->data[i].allocated) {
			index = i;
			break;
		}
	}
	if (index < 0)
		index = self->capacity;

	// adjust minFreeIndex and maxAllocatedIndex to account for the newly allocated index
	i = index + 1;
	while (i < self->capacity && self->data[i].allocated)
		i++;
	self->minFreeIndex = i;

	if (index > self->maxAllocatedIndex)
		self->maxAllocatedIndex = index;

	// if the index overflows the current capacity, increase the capacity
	if (index >= self->capacity) {
		int newCapacity = self->capacity * CAPACITY_MULTIPLIER;
		resizeData(self, newCapacity);
	}

	// set the allocated flag for the slot
	self->data[index].allocated = 1;

	// return the index
	return index;
}

// deallocate the pointer at the given index, this will not free and additional
// resources pointed to by the 
void CodonAllocator_release(CodonAllocator* self, int index) {
	// unallocated index, does nothing
	if (index < 0 || index >= self->capacity || !self->data[index].allocated)
		return;

	// clear the allocated data slot, null out the pointer as well
	self->data[index].allocated = 0;
	self->data[index].value = NULL;

	// adjust minFreeIndex and maxAllocatedIndex to account for the newly allocated index
	int i = self->maxAllocatedIndex;
	while (i >= 0 && !self->data[i].allocated)
		i--;
	self->maxAllocatedIndex = i;

	if (index < self->minFreeIndex)
		self->minFreeIndex = index;

	// if the maxAllocatedIndex is sufficiently small, trim excess space
	// from the array
	int maxAllocatedCount = self->maxAllocatedIndex + 1;
	if (maxAllocatedCount * CAPACITY_MULTIPLIER * CAPACITY_MULTIPLIER < self->capacity) {
		int newCapacity = maxAllocatedCount * CAPACITY_MULTIPLIER;

		if (newCapacity < 1)
			newCapacity = 1;

		resizeData(self, newCapacity);
	}
}
