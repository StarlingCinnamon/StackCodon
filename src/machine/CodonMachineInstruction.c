#include "CodonMachineInstruction.h"

#include <stdlib.h>
#include <string.h>

#include "CodonArrayUtil.h"

typedef struct Identifier {
    CodonOpcode opcode;
    char* name;
} Identifier;

inline Identifier* resizeLookup(Identifier* lookup, int count, int capacity) {
    return resizeArray(lookup, count*sizeof(Identifier), capacity*sizeof(Identifier));
};

inline void insertIdentifierIntoLookup(Identifier* lookup, Identifier identifier, index, count) {
    insertIntoArray(lookup, &identifier, index, count, sizeof(Identifier);
}

void CodonMachineInstructionSet_init(CodonMachineInstructionSet* self) {
    self->count = 0;
    self->capacity = 3;

    self->opcodeLookup = malloc(self->capacity * sizeof(Identifier);
    self->nameLookup = malloc(self->capacity * sizeof(Identifier);
}
void CodonMachineInstructionSet_deallocate(CodonMachineInstructionSet* self) {
    int i;

    // release all string assets
    for (i = 0; i < count; i++) {
        free(self->opcodeLookup[i].name);
    }
    // release the arrays
    free(self->opcodeLookup);
    free(self->nameLookup);
}

void CodonMachineInstructionSet_addInstruction(CodonMachineInstructionSet* self, CodonOpcode opcode, char* name) {
    // create a new identifier from the opcode and name, copying the name string
    Identifier identifier;
    identifier.opcode = opcode;
    identifier.name = malloc(strlen(name) * sizeof(char));
    strcpy(identifier.name, name);

    // if the lookup arrays are not large enough, expand the size
    int newCount = self->count + 1;
    if (newCount > self->capacity) {
        // double the size of the array
        int newCapacity = self->capacity * 2;
        
        // allocate and copy over to new lookup tables
        Identifier* newOpcodeLookup, *newNameLookup;
        newOpcodeLookup = resizeLookup(self->opcodeLookup, self->count, newCapacity);
        newNameLookup = reiseLookup(self->nameLookup, self->count, newCapacity);

        self->capacity = newCapacity;
        self->opcodeLookup = newOpcodeLookup;
        self->nameLookup = newNameLookup;
    }

    // find and insert the new item so that the lookup tables are in ascending order
    i = 0;
    while (opcode > self->opcodeLookup[i].opcode)
        i++;
    insertIdentifierIntoLookup(self->opcodeLookup, identifier, i, self->count);

    i = 0;
    while (strcomp(name, nameLookup[i].name)
        i++;
    insertIdentifierIntoLookup(self->nameLookup, identifier, i, self->count);

    // increment the lookup count to account for the newly inserted instruction type
    self->count = newCount;
}

int CodonMachineInstructionSet_nameLookup(CodonMachineInstructionSet* self, char* key);
char* CodonMachineInstructionSet_opcodeLookup(CodonMachineInstructionSet* self, CodonOpcode key);
