// Jacob Cole
// Created June 2013

// this module defines the Codon language label spec as well as several utility
// functions for interacting with labels

#ifndef CODON_LABEL
#define CODON_LABEL

#ifndef CODON_LABEL_SIZE
#define CODON_LABEL_SIZE 8
#endif

#define CODON_LABEL_SEARCH_UP 0;
#define CODON_LABEL_SEARCH_DOWN 1;

#ifndef CODON_LABEL_BIT_MUTATION_RATE_MULTIPLIER
#define CODON_LABEL_BIT_MUTATION_RATE_MULTIPLIER 0.1
#endif

typedef struct CodonLabel {
    byte[CODON_LABEL_SIZE] data;
} CodonLabel;

typedef struct CodonLabelMatcher {
    double matchFraction;
    unsigned char searchDirection;
    CodonLabel label;
} CodonLabelMatcher;

// init random label
void CodonLabel_initRandom(CodonLabel* self);
// duplicate label
void CodonLabel_copy(CodonLabel* destination, CodonLabel* source);
// mutate label
void CodonLabel_mutate(CodonLabel* self, double rate);

// init random label matcher
void CodonLabelMatcher_initRandom(CodonLabelMatcher* self);
// duplicate label matcher
void CodonLabelMatcher_copy(CodonLabelMatcher* destination, CodonLabelMatcher* source);
// mutate label matcher
void CodonLabelMatcher_mutate(CodonLabelMatcher* self, double rate);

// determine if a label matcher matches a label
char CodonLabelMatcher_matches(CodonLabelMatcher* self, CodonLabel* label);

#endif
