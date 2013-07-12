#include "CodonMemoryAllocator.h"

#include <stdio.h>

void printAllocatorState(CodonMemoryAllocator* memoryAllocator) {
	CodonAllocator* allocator = &(memoryAllocator->allocator);

	int i;

	printf("capacity = %i\n", allocator->capacity);

	for (i = 0; i < allocator->capacity; i++) {
		CodonAllocatorValue value = allocator->data[i];
		int alloc = value.allocated;
		int refCount = -1, pointer = -1;
		if (alloc) {
			CodonMemoryAllocatorStack* stack = value.value;
			refCount = stack->referenceCount;
			pointer = (int)(&(stack->stack));
		}

		printf("index %i ~ alloc %i ~ refCount %i ~ ptr %i\n", i, alloc, refCount, pointer);
	}
}

int main(int argc, char** argv) {
    CodonMemoryAllocator* memoryAllocator = CodonMemoryAllocator_new(3);

    int i;

    CodonStack* indexStack = CodonStack_new(10);

	printf("Empty Allocator\n");
	printAllocatorState(memoryAllocator);
    printf("\n");

    for (i = 0; i < 5; i++) {
        int index = CodonMemoryAllocator_allocate(memoryAllocator);
        CodonStack_push(indexStack, (double)index);
        printf("allocated stack: index = %i\n", i);
    }

	printf("Added Some\n");
	printAllocatorState(memoryAllocator);
    printf("\n");

    //CodonMemoryAllocator_release(memoryAllocator, 1);
    CodonMemoryAllocator_release(memoryAllocator, 2);
    CodonMemoryAllocator_retain(memoryAllocator, 3);

	printf("Release index 2, retain index 3\n");
	printAllocatorState(memoryAllocator);
    printf("\n");

    CodonMemoryAllocator_release(memoryAllocator, 3);

	printf("Release 3\n");
	printAllocatorState(memoryAllocator);
    printf("\n");

    CodonMemoryAllocator_allocate(memoryAllocator);
    CodonMemoryAllocator_allocate(memoryAllocator);
    CodonMemoryAllocator_allocate(memoryAllocator);

	printf("Allocate 3 more\n");
	printAllocatorState(memoryAllocator);
    printf("\n");

    CodonMemoryAllocator_release(memoryAllocator, 0);
    CodonMemoryAllocator_release(memoryAllocator, 1);
    CodonMemoryAllocator_release(memoryAllocator, 2);
    CodonMemoryAllocator_release(memoryAllocator, 3);
    CodonMemoryAllocator_release(memoryAllocator, 4);
    CodonMemoryAllocator_release(memoryAllocator, 5);
    CodonMemoryAllocator_release(memoryAllocator, 6);

	printf("Release indices 0 to 6\n");
	printAllocatorState(memoryAllocator);
    printf("\n");
	
    CodonMemoryAllocator_delete(memoryAllocator);

	printf("Allocator Deleted\n");

    return 0;
}
