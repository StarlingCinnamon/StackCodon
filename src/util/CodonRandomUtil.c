#include "CodonRandomUtil.h"

#include <stdlib.h>

double CodonRandomDouble() {
    return (double)rand() / (double)RAND_MAX;
}

char CodonRandomBool(double chance) {
    return CodonRandomDouble() > chance;
}
