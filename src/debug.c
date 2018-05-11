#include <stdio.h>

#include "../include/debug.h"
#include "../include/tsp.h"

void print_parameters(void)
{
    int count = 0;

    for (count = 1; count < last; count++) {
	printf("%s\t%s\n", parameters[count].name,
	       parameters[count].value);
    }

}
