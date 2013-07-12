#include "CodonLabel.h"

#include <stdlib.h>

#include "CodonRandomUtil.h"

// ============================================================================
// calculate the number of set bits in a unsigned char
// from "Bit Twiddling Hacks" http://graphics.stanford.edu/~seander/bithacks.html
static const unsigned char BitsSetTable256[256] = 
{
#   define B2(n) n,     n+1,     n+1,     n+2
#   define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
#   define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
    B6(0), B6(1), B6(1), B6(2)
};

int bitsSetCount(unsigned char value) {
    return BitSetTable256[value];
}

// ============================================================================
void CodonLabel_initRandom(CodonLabel* self) {
    int i;
    for (i = 0; i < CODON_LABEL_SIZE; i++)
        self->data[i] = rand() % UCHAR_MAX;
}

void CodonLabel_copy(CodonLabel* destination, CodonLabel* source) {
    memcpy(destination->data, source->data, CODON_LABEL_SIZE * sizeof(char));
}

void CodonLabel_mutate(CodonLabel* self, double rate) {
    int lengthInBytes = CODON_LABEL_SIZE * 8/*bits in byte*/;
    int i, byteIndex, bitIndex;
    unsigned char mask;
    for (i = 0; i < lengthInBytes; i++) {
        if (CodonRandomBool(rate * CODON_LABEL_BIT_MUTATION_RATE_MULTIPLIER)) {
            byteIndex = i / 8/*bits in byte*/;
            bitIndex = i % 8/*bits in a byte*/;
            
            // flip the bit at that index
            mask = 1 << bitIndex;
            self->data[byteIndex] ^= mask;
        }
    }
}

void CodonLabelMatcher_initRandom(CodonLabelMatcher* self) {
    self->matchFraction = CodonRandomDouble();
    if (CodonRandomBool(0.5))
        self->searchDirection = CODON_LABEL_SEARCH_UP;
    else
        self->searchDirection = CODON_LABEL_SEARCH_DOWN;

    CodonLabel_init(&(self->label));
}

void CodonLabelMatcher_copy(CodonLabelMatcher* destination, CodonLabelMatcher* source) {
    destination->matchFraction = source->matchFraction;
    destination->searchDirection = source->sourceDirection;

    CodonLabel_copy(&(destination->label), &(source->label));
}

void CodonLabelMatcher_mutate(CodonLabelMatcher* self, double rate);


char CodonLabelMatcher_matches(CodonLabelMatcher* self, CodonLabel* label) {
    // calculate the number of bits in common
    int i, matchingBitCount = 0;
    for (i = 0; i < CODON_LABEL_SIZE; i++) {
        // matching bits are 1, not matching 0
        char commonBits = ~(self->label[i].data ^ label.data[i]);

        matchingBitCount += bitSetCount(commonBits)
    }

    // calculate the fraction of bits that match
    double fractionSet = (double)matchingBitCount / (double)(CODON_LABEL_SIZE * 8/*bits in byte*/);
    
    return fractionSet > self->matchFraction;
}
