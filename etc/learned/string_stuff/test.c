#include <string.h>
#include <stdio.h>


int replace_char(char *str, char old_char, char new_char);


int main(void)
{
  int result = 0;
  char str[] = "this is my test string";

  result = replace_char(str, ' ', '_');
  printf("\n%s\n%d replacments", str, result);

  return 0;
}





int replace_char(char *str, char old_char, char new_char)
{
  int count = 0;
  int made_change_flag = 0;

  for(count = 0; count < (int)strlen(str); count ++)
  {
    if(str[count] == old_char)
    {
      str[count] = new_char;
      made_change_flag++;
    }


  }

  return made_change_flag;
}
