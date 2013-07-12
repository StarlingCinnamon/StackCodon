#include "CodonMachineInstruction.h"

int main(int argc, char** argv) {
    CodonMachineInstructionSet instructionSet;

    CodonMachineInstructionSet_init(&instructionSet);
    
    CodonMachineInstructionSet_addInstruction(&instructionSet, 0, "NOP");
    
    CodonMachineInstructionSet_addInstruction(&instructionSet, 100, "JUMPTO");
    CodonMachineInstructionSet_addInstruction(&instructionSet, 200, "IF");
    CodonMachineInstructionSet_addInstruction(&instructionSet, 300, "NEWSTACK");
    CodonMachineInstructionSet_addInstruction(&instructionSet, 301, "REFERENCE");
    CodonMachineInstructionSet_addInstruction(&instructionSet, 400, "IOSIZE");
    CodonMachineInstructionSet_addInstruction(&instructionSet, 401, "IOPOP");
    CodonMachineInstructionSet_addInstruction(&instructionSet, 402, "IOPUSH");

    CodonMachineInstructionSet_dealloc(&instructionSet);

    return 0;
}
