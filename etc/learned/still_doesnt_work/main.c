#include <stdio.h>
#include "main.h"

int global_int = 1;

int main(void)
{
  add_one();
  printf("The value of global_int is %d\n", global_int);
}
