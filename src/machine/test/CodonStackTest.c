
#include <stdio.h>
#include "CodonStack.h"

int main(int argc, char** argv) {
    int i;
    double value;

    CodonStack* stack = CodonStack_new(3);

    for (i = 0; i < 10; i++) {
        CodonStack_push(stack, i);
    }

    for (i = 0; i < 5; i++) {
        value = CodonStack_pop(stack);
        printf("%f\n", value);
        printf("Length = %i\n", stack->capacity);
    }

    for (i = 0; i < 10; i++) {
        CodonStack_push(stack, i+100);
    }

    for (i = 0; i < 25; i++) {
        value = CodonStack_pop(stack);
        printf("%f\n", value);
        printf("Length = %i\n", stack->capacity);
    }

    CodonStack_delete(stack);

    return 0;
}
