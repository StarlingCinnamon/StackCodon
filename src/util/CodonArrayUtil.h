// Jacob Cole
// Created June 2013

// this provides some array utility functions for use with the
// CodonStack project

#ifndef CODON_ARRAY_H
#define CODON_ARRAY_H

// return a new array resized to capacity bytes, with count copied over bytes
void* resizeArray(void* data, int count, int capacity);

// insert the value into the array at the specified array index
// count is the original size of the array
// size defines the size of the array values in bytes
void insertIntoArray(void* data, void* value, int index, int count, int size);

#endif
