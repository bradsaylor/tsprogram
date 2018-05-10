#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "../include/menu_funcs.h"
#include "../include/tsp.h"
#include "../include/util.h"

int validate_input(char *input)
{ 
  if(!strcmp(input,""))
  {
    menu();
    return 0;
  } 
  else if(!strcmp(input,"1"))
  {
    edit(atoi(input));
    return 0;
  }
  else if(!strcmp(input,"2"))
  {
    edit(atoi(input));
    return 0;
  }
  else if(!strcmp(input,"3"))
  {
    edit(atoi(input));
    return 0;
  }
  else if(!strcmp(input,"4"))
  {
    edit(atoi(input));
    return 0;
  }
  else if(!strcmp(input,"5"))
  {
    edit(atoi(input));
    return 0;
  }
  else if(!strcmp(input,"6"))
  {
    edit(atoi(input));
    return 0;
  }
  else if(!strcmp(input,"7"))
  {
    edit(atoi(input));
    return 0;
  }
  else if(!strcmp(input,"8"))
  {
    edit(atoi(input));
    return 0;
  }
  else if(!strcmp(input,"9"))
  {
    edit(atoi(input));
    return 0;
  }
  else if(!strcmp(input,"10"))
  {
    edit(atoi(input));
    return 0;
  }
  else if(!strcmp(input,"11"))
  {
    edit(atoi(input));
    return 0;
  }
  else if(!strcmp(input,"12"))
  {
    edit(atoi(input));
    return 0;
  }
  else if(!strcmp(input,"n"))
  {
    name();
    return 0;
  }
  else if(!strcmp(input,"g"))
  {
    group();
    return 0;
  }
  else if(!strcmp(input,"s"))
  {
    save();
    return 0;
  }
  else if(!strcmp(input,"o"))
  {
    open();
    return 0;
  }
  else if(!strcmp(input,"r"))
  {
    reference();
    return 0;
  }
  else if(!strcmp(input,"t"))
  {
    tolerance();
    return 0;
  }
  else if(!strcmp(input,"v"))
  {
    variance();
    return 0;
  }
  else if(!strcmp(input,"m"))
  {
    target();
    return 0;
  }
  else if(!strcmp(input,"q"))
  {
    quit();
    return 0;
  }
  else if(!strcmp(input,"a"))
  {
    calc();
    return 0;
  }
  else return 1;


}

int menu(void)
{
  return 0;
}

int edit(int parameter_index)
{
  char new_value[MAX_VALUE_LENGTH];
  
  printf("Enter value for %s: ", parameters[parameter_index].name);
  fgets(new_value, sizeof(new_value), stdin);
  replace_char(new_value, 10, 0);
  strcpy(parameters[parameter_index].value, new_value);
  
  return 0;
}

int name(void)
{
  char file_name_input[MAX_NAME_LENGTH];
  int blank_name_check = 0;
  int count = 0;
  
  while(!blank_name_check)
  {    
    printf("Enter file name: ");
    fgets(file_name_input, sizeof(file_name_input), stdin);

    strcpy(file_name, file_name_input);

    // if name is not blank set flag and exit loop
    for(count = 0; count < (int)strlen(file_name); count++)
    {
      if(isalnum(file_name[count])) blank_name_check = 1;
    }
  }

  // replace ending line feed with string null termination
  replace_char(file_name, 10, 0);

  // replace any spaces or slashes with underscores
  // promp if you did
  if(replace_char(file_name, ' ', '_') ||
     replace_char(file_name, '/', '_') ||
     replace_char(file_name, '\\', '_'))
  {
    printf("\nReformatted to -> %s", file_name);    
  }

  return 0;
}

int group(void)
{

  return 0;
}

int save(void)
{
  FILE *fp_group_file;
  char file_line[MAX_FILE_LINE];
  char parsed_name[MAX_NAME_LENGTH];
  char parsed_value[MAX_NAME_LENGTH];
  char copied_from_file[MAX_FILE_LENGTH][MAX_NAME_LENGTH];

  int data_write_counter = 0;
  int copied_counter = 0;
  int file_line_count = 0;
  int insert_point = 0;

  //** Check to see if a group name has been given
  //*** If not make a group name using file name
  //*** If so do nothing and continue
  if(!strcmp(file_name, empty_label))
  {
    name();
  }

  //** Check to see if a name has been given
  //*** If not send to name() routine
  //*** If so do nothing and continue
  if(!strcmp(group_name, empty_label))
  {
    strcpy(group_name, file_name);
  }

  //** Open file
  char group_name_ext[MAX_NAME_LENGTH + 3];
  sprintf(group_name_ext, "%s%s", group_name, FILE_EXTENSION);
  fp_group_file = fopen(group_name_ext, "a+");

  //** Check to see if file size plus pending data will exceed limit
  //*** If so display error and exit back to main()
  //*** If not continue
  if(check_file_length(group_name, 1000, 300))
  {
    fclose(fp_group_file);
    printf("\nFile length too long exceeds %d lines\n", MAX_FILE_LENGTH);
    return 1;
  }

  //  ** If target flag is set then re-write file replacing any "ref: Y" with "ref: N"
  

  //** Search through .grp file to find alphabetic insert point
  //*** If found start caching existing file lines and writing out data
  //**** When data write is finished append a blank line
  //**** Write out the cached data appended below the blank line
  //*** If not found append data to end of file
  

  // Determine insert point:  grab line from file while insert point not found
  while(fgets(file_line, MAX_FILE_LINE, fp_group_file)!=NULL)
  {
    file_line_count++;

    // sscanf returns EOF if scan is not successful i.e. when reading a blank line
    if(sscanf(file_line, "%s %s", parsed_name, parsed_value)!=EOF)
    {
      if(insert_point ==0){
	if(!strcmp(parsed_name, "name:"))
	{
	  if(strcmp(parsed_value, file_name) > 0) insert_point = file_line_count;
	}
      }
      if (insert_point != 0)
      {
	strcpy(copied_from_file[copied_counter], file_line);
	copied_counter++;
	if(data_write_counter < (LINES_PER_WRITE + 1))
	{
//	 	  fprintf(fp, "%s\t%s", )
	}
	
      }
    }

    
  }

  fclose(fp_group_file);

  return 0;
}

int open(void)
{

  return 0;
}

int reference(void)
{

  return 0;
}

int tolerance(void)
{

  return 0;
}

int variance(void)
{

  return 0;
}

int target(void)
{

  return 0;
}

int quit(void)
{

  return 0;
}

int calc(void)
{

  return 0;
}

