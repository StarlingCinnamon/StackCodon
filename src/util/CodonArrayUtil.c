#include "CodonArrayUtil.h"

#include <stdlib.h>
#include <string.h>

inline void* resizeArray(void* data, int count, int capacity) {
    // create a new array and fill it with the old data
    void* newData = malloc(capacity);
    memcpy(newData, data, count);

    free(data);

    return newData;
}

inline void insertIntoArray(void* data, void* value, int index, int count, int size) {
    // shift the data following the index
    memmove(data + index * size, data + (index + 1) * size, (count - index) * size);
    // copy the data value into the spot
    memcpy(data + index * size, value, size);
}
