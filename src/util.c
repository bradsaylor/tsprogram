#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

#include "../include/util.h"


int check_file_length(char *name, int max_file_size, int max_file_line)
{
  int number_of_lines = 0;

  number_of_lines = count_file_lines(name, max_file_line);

  if(number_of_lines == -1) return 2;

  if(number_of_lines > (max_file_size - 1))
  {
    return 1;
  } 

  return 0;
}

int append_to_file(char *name, char *add_string)
{
  FILE *fp;
  int result = 0;

  fp = fopen(name, "a+");
  result = fprintf(fp, "%s", add_string);
  fclose(fp);

  return result;
}

int list_file_numbered(char *name, int max_file_line)
{
  FILE *fp;
  char file_line[max_file_line];
  int line_number = 0;

  fp = fopen(name, "r");
  if(fp == NULL) return 1;

  while(fgets(file_line, max_file_line, fp) != NULL)
  {
    line_number++;
    printf("[%d]  %s", line_number, file_line);
  }

  fclose(fp);

  return 0;
}

int count_file_lines(char *name, int max_file_line)
{
  FILE *fp;
  int line_count = 0;
  char file_line[max_file_line];

  fp = fopen(name, "a");
  fclose(fp);

  fp = fopen(name, "r");
  if(fp == NULL) return -1;

  while (fgets(file_line, max_file_line, fp) !=NULL)
  {
    line_count++;
  }

  fclose(fp);

  return line_count;
}

int delete_file_line(char *name, int line_to_delete)
{
  FILE *fp;
  FILE *temp_fp;
  char file_character;
  int line_count = 0;

  fp = fopen(name, "r+");
  temp_fp = fopen("temp.txt", "w");
  
  file_character = fgetc(fp);

  while(file_character != EOF)
  {
    if(line_count != (line_to_delete - 1))
    {
      putc(file_character, temp_fp);      
    }

    if(file_character == '\n')
    {
      line_count++;
    }
    file_character = fgetc(fp);
  }
  
  fclose(fp);
  fclose(temp_fp);
  remove(name);
  rename("temp.txt", name);
  
  return 0;
}

int replace_char(char *str, char old_char, char new_char)
{
  int count = 0;
  int made_change_flag = 0;

  for(count = 0; count < (char)strlen(str); count++)
  {
    if(str[count] == old_char)
    {
      str[count] = new_char;
      made_change_flag++;
    }
  }

  return made_change_flag;
}

int check_input_length(char *str, char max_input_length)
{
  int length;
  length = strlen(str);
  if(length > max_input_length) return 1;
  return 0;
}

int input_nonzero_int(char *input)
{
  int number;

  number = atoi(input);
  return number;

}

int print_file_line(char *name, int file_line)
{
  FILE *fp;
  int line_count = 1;
  char file_char = ' ';

  if(file_line > count_file_lines(name, 100))
  {
    printf("\nLine is beyond length of file\n");
    return 1;
  }

  fp = fopen(name, "r");
  
  while(file_char != EOF)
  {
    file_char = fgetc(fp);

    if(line_count == file_line)
    {
      while(file_char != '\n')
      {
	printf("%c", file_char);
	file_char = fgetc(fp);
      }
    }
    if(file_char == '\n') line_count++;    
  }

  return 0;
}

int search_file_delimited(char *name, char *delim_f, char *delim_b, char *search)
{
  int MAX_SEARCH_BUFFER = 1000;
  char search_buffer[MAX_SEARCH_BUFFER];
  char delim_f_buffer[strlen(delim_f) + 1];
  char delim_b_buffer[strlen(delim_b) + 1];
  char file_char = ' ';
  char *search_return = NULL;
  FILE *fp;
  int i = 0;
  int search_buffer_count = 0;
  int found_b_delim = 0;
  int file_check = 0;
  
  //Check to make sure file exists and has read privelages
  //if not return error code 2
  file_check = open(name, O_RDONLY);
  if(file_check == -1)
  {
    printf("\nfile does not exist\n");
    return 2;
  }
  fp = fopen(name, "r");

  //place null terminator at end of buffers
  delim_f_buffer[(int)strlen(delim_f)] = '\0';
  delim_b_buffer[(int)strlen(delim_b)] = '\0';

  file_char = fgetc(fp);

  while(file_char != EOF)
  {
    //get char from file
    file_char = fgetc(fp);
    //shift delim_f_buffer to the left
    for(i = 0; i < ((int)strlen(delim_f_buffer) - 1); i++)
    {
      delim_f_buffer[i] = delim_f_buffer[i+1];
    }
    //replace last value of delim_f_buffer with file_char
    delim_f_buffer[(int)strlen(delim_f) - 1] = file_char;

    //if delim_f_buffer matches front delimiter
    if(!strcmp(delim_f, delim_f_buffer))
    {      while(found_b_delim == 0)
      {
	//get char from file
	file_char = fgetc(fp);

	//put file char in search buffer
	if(search_buffer_count < (MAX_SEARCH_BUFFER - 2))
	{
	  search_buffer[search_buffer_count] = file_char;
	  search_buffer_count++;
	}else
	{
	  printf("\nsearch buffer overflow\n");
	  return 1;
	}

	//shift delim_b_buffer to the left
	for(i = 0; i < ((int)strlen(delim_f_buffer) - 1); i++)
	{
	  delim_b_buffer[i] = delim_b_buffer[i+1];
	}
	//replace last value of delim_b_buffer with file_char
	delim_b_buffer[(int)strlen(delim_b) - 1] = file_char;

	//if delim_buffer matches back delimiter
	if(!strcmp(delim_b, delim_b_buffer))
	{
	  found_b_delim = 1;
	  search_buffer[search_buffer_count] = '\0';
	}
      }
    }

    //reset found_b_delim and search_buffer_count
    found_b_delim = 0;
    search_buffer_count = 0;

    //reset delim buffers
    for (i = 0; i < (int)strlen(delim_f) - 1; i++)
    {
      delim_f_buffer[i] = ' ';
    }
    for (i = 0; i < (int)strlen(delim_b) - 1; i++)
    {
      delim_b_buffer[i] = ' ';
    }

    /****** SEARCH BUFFER FOR DESIRED TERM *******/
    search_return = strstr(search_buffer, search);
    /****** PRINT BUFFER IF FOUND ****************/
    if(search_return != NULL)
    {
      printf("\n%s\n", search_buffer);
      for(i = 0; i < MAX_SEARCH_BUFFER; i++)
      {
	search_buffer[i] = ' ';
      }
    }
    
  }

  return 0;
}

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

int rewind_line(char *print_string)
{
     char x;
     char exit_string[]  = " ...any key";

     printf("%s", print_string);
     printf("%s", exit_string);
     x = getch();

     for(int x = 0; x < ((int)strlen(print_string) + (int)strlen(exit_string)); x++) {
	  putchar('\b');
	  putchar(' ');
	  putchar('\b');
     }

     return 0;
}

int bash_resize(int x, int y)
{
     char str[30] = "";

     sprintf(str, "echo -ne \"\e[8;%d;%dt\"", y, x);
     system(str);
     return 0;
}

int print_table(int rows, int columns, int cell_size)
{
     const int row_count = (2 * rows + 1), column_count = columns * (cell_size + 1) + 1;

     char display_array[row_count][column_count + 2];

     for(int i = 0; i < row_count; i++){
	  for(int j = 0; j < column_count + 2; j++){

	       if (j == column_count){
		    display_array[i][j] = '\n';
	       }

	       else if (j == column_count + 1){
		    display_array[i][j] = '\0';
	       }


	       else if  (!(i%2)){
		    display_array[i][j] = '-';
	       }


	       else if (!(j%(cell_size + 1))){
		    display_array[i][j] = '|';
	       }

	       else display_array[i][j] = ' ';
	  }
     }

     for(int i = 0; i < row_count; i++){
	  printf("%s", display_array[i]);
     }

     return 0;
}

int check_file_for_string(char *name, char *str, int search_buffer_size)
{
    char search_buffer[search_buffer_size];
    char file_char;
    int file_char_count = 0;
    FILE *fp;

    fp = fopen(name, "r");
    file_char = getc(fp);

    while(file_char != EOF) {
	search_buffer[file_char_count] = file_char;
	file_char_count++;
	
	if(file_char_count >= (search_buffer_size - 1)) {
	    printf("\nsearch buffer overload\n");
	    return 2;
	}
	file_char = getc(fp);
    }

    // place null terminator at end of read chars
    search_buffer[file_char_count + 1] = '\0';

    if(strstr(search_buffer, str) != NULL) return 0;
    

    return 1;    
}

int get_datestamp(char *str)
{
    struct tm *timeinfo;
    time_t current_time;

    time(&current_time);
    timeinfo = localtime(&current_time);
    sprintf(str, "%d-%02.0f-%02.0f",
	    timeinfo->tm_year + 1900, (float)timeinfo->tm_mon + 1.0, (float)timeinfo->tm_mday);
    
    return 0;
}
