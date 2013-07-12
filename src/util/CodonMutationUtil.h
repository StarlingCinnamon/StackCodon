// Jacob Cole
// Created June 2013

// utility functions for mutating values

#ifndef CODON_MUTATION_UTIL_H
#define CODON_MUTATION_UTIL_H

// mutate the value linearly within the range [value - range, value + range]
// clamped in the [min, max] range
double CodonMutateLinearClamped(double min, double max, double range, double value);

// mutate the value linearly within the range [value - range*value, value + range * value]
// clamped to the [min, max] range
double CodonMutateLinearPowerClamped(double min, double max, double range, double value);

#endif
