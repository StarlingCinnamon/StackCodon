
#include <stdio.h>
#include "CodonStack.h"

int main(int argc, char** argv) {
    int i;
    double value;

    CodonStack* stack = CodonStack_new(3);

	printf("new stack: size = %i\n", CodonStack_size(stack));

	CodonStack_push(stack, 20);

	printf("pushed a value: size = %i\n", CodonStack_size(stack));

    for (i = 0; i < 10; i++) {
        CodonStack_push(stack, i);
    }
	printf("pushed 10 values\n");

    for (i = 0; i < 5; i++) {
		printf("pop\n");
        value = CodonStack_pop(stack);
        printf("%f\n", value);
        printf("Length = %i\n", stack->capacity);
		printf("Size = %i\n", CodonStack_size(stack));
    }

    for (i = 0; i < 10; i++) {
        CodonStack_push(stack, i+100);
    }
	printf("pushed 10 values\n");

    for (i = 0; i < 25; i++) {
		printf("pop\n");
        value = CodonStack_pop(stack);
        printf("%f\n", value);
        printf("Length = %i\n", stack->capacity);
		printf("Size = %i\n", CodonStack_size(stack));
    }

    CodonStack_delete(stack);

    return 0;
}
