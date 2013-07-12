// Jacob Cole
// Created June 2013

#ifndef CODON_MACHINE_INSTRUCTION_H
#define CODON_MACHINE_INSTRUCTION_H

typedef int CodonOpcode;
typedef int CodonMachineInstructionIdentifier;

typedef struct CodonMachineInstructionIdentifier {
	CodonOpcode opcode;
	char* name;
} CodonMachineInstructionIdentifier;

typedef struct CodonMachineParameter {
    union {
        int relativeAddress;
        int variableIndex;
        double literal;
    };
} CodonMachineParameter;

#define CODON_MACHINE_PARAMETER_COUNT 2

typedef struct CodonMachineInstruction {
    CodonOpcode opcode;
    CodonMachineParameter *parameters[CODON_MACHINE_PARAMETER_COUNT];
} CodonMachineInstruction;

// ============================================================================

typedef struct CodonMachineInstructionSet {
    int count;
    int capacity;
    CodonMachineInstructionIdentifier* opcodeLookup;
    CodonMachineInstructionIdentifier* nameLookup;
} CodonMachineInstructionSet;

void CodonMachineInstructionSet_init(CodonMachineInstructionSet* self);
void CodonMachineInstructionSet_deallocate(CodonMachineInstructionSet* self);

void CodonMachineInstructionSet_addInstruction(CodonMachineInstructionSet* self, CodonOpcode opcode, char* name);

int CodonMachineInstructionSet_nameLookup(CodonMachineInstructionSet* self, char* key);
char* CodonMachineInstructionSet_opcodeLookup(CodonMachineInstructionSet* self, CodonOpcode key);

#endif
