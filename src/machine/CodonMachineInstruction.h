// Jacob Cole
// Created June 2013

#ifndef CODON_MACHINE_INSTRUCTION_H
#define CODON_MACHINE_INSTRUCTION_H

#include "CodonMachine.h"

typedef int CodonOpcode;

typedef struct CodonMachineInstruction {
	CodonOpcode opcode;
	void execute(CodonMachine* machine, CodonMachineParameter*);
} CodonInstruction;

typedef struct CodonMachineParameter {
    union {
        int relativeAddress;
        int variableIndex;
        double literal;
    };
} CodonMachineParameter;

#define CODON_MACHINE_PARAMETER_COUNT 2

typedef struct CodonMachineInstruction {
    CodonInstruction* instruction;
    CodonMachineParameter *parameters[CODON_MACHINE_PARAMETER_COUNT];
} CodonMachineInstruction;

#endif
