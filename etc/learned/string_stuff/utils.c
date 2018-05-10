#include <string.h>

int replace_char(char *str, char old_char, char new_char)
{
  char count = 0;
  char *str_ptr;
  int made_change_flag = 0;

  str_ptr = str;

  for(count = 0; count < (char)strlen(str); count++)
  {
    if(*str_ptr == old_char)
    {
      *(str) = new_char;
      made_change_flag++;
    }
    str_ptr++;
  }

  return made_change_flag;
}
