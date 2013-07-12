// Jacob Cole
// Created June 2013

#ifndef CODON_MACHINE_H
#define CODON_MACHINE_H

#include "CodonMachineInstruction.h"

typedef struct CodonThread {
    char isAlive;

    int instructionPointer;
    int cyclesPerTick;
}

typedef struct CodonMachine {
	// instructions currently loadede into the machine
	int instructionCount;
    CodonMachineInstruction* instructions;

	// memory allocator utility
    CodonMemoryAllocator* memoryAllocator;
    
	// active threads
    CodonThread* threads;
}

CodonMachine* CodonMachine_newEmpty();

CodonMachine* CodonMachine_tick();
CodonMachine

#endif
