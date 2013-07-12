CC = gcc
INC = -I. -I./util -I./machine -I./machine/test

StackTest:
	$(CC) $(INC) machine/test/CodonStackTest.c machine/CodonStack.c  util/CodonArrayUtil.c -o StackTest

MemoryAllocatorTest:
	$(CC) $(INC) machine/test/CodonMemoryAllocatorTest.c machine/CodonMemoryAllocator.c machine/CodonStack.c util/CodonAllocator.c util/CodonArrayUtil.c -o MemoryAllocatorTest
