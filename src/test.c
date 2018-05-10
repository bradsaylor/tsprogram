#include <stdio.h>
#include "../include/util.h"

int main(void)
{
  char *str = "this is my test string";

  replace_char(str, ' ',  '_');

  printf("\n%s\n", str);


  return 0;  
  
}
	
