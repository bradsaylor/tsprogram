#ifndef UTIL_H_
#define UTIL_H_

//function prototypes and documentation

int append_to_file(char *name, char *add_string);
/*
  ***** int append_to_file(char *name, char *add_string) *****
  Appends string 'add_string' to end of file 'name'

  REQUIRES: add_string -> string to append
            name       -> name of file

  RETURNS:  non-negative int ->  if file print was successful
                negative int ->  if file print was unsuccessful
________________________________________________________________ */

int list_file_numbered(char *name, int max_file_line);
/*
  ***** int list_file(char *name, int max_file_line) *****
  Prints contents of file 'name' line by line.  Each line recieves
  an index number [#].  Prints a maximum number of chars per line 'max_file_line'

  REQUIRES:  max_file_line -> Max number of chars in a file line
             name          -> Name of file

  RETURNS:  0 -> if file was opened sucessfully
            1 -> if file did not open successfully
_______________________________________________________________ */

int check_file_length(char *name, int max_file_size, int max_file_line);
/*
  ***** int check_file_length(char *name, int max_file_size, int max_file_line) *****
  Computes number of lines in file 'name' reading a maximum number of chars
  per line 'max_file_line'.  If size of file is greater than 'max_file_size'
  an error is returned.

  REQUIRES:  max_file_line -> Max number of chars in a file line
             max_file_size -> Max number of lines in a file
             name          -> name of file

  RETURNS:  0:  If file does not exceed max length
            1:  If file exceeds max length
            2:  If cannot open file
__________________________________________________________________________ */

int count_file_lines(char *name, int max_file_line);
/*
  ***** int count_file_lines(char *name, int max_file_line) *****
  Counts the number of lines in file 'name'.  

  REQUIRES:  max_file_line -> Max number of chars in a file line
             name          -> Name of file

  RETURNS:  # of lines counted -> if successfull
            -1                 -> if cannot open file
__________________________________________________________________________ */

int delete_file_line(char *name, int line_to_delete);
/*
  ***** int delete_file_line(char *name, int line_to_delete) *****
  Deltets specified line 'line_to_delete' from file 'name'

  REQIURES:  line_to_delete -> line to delete
             name           -> file name

  RETURNS:  0 -> no error checking
__________________________________________________________________________ */

int replace_char(char *str, char old_char, char new_char);
/*
  ***** int replace_char(char *str, char old_char, char new_char) *****
  replaces specified char 'old_char' with specified char 'new_char' in 
  string 'str'

  REQUIRES:  old_char -> character to replace
             new_char -> character to insert
             str      -> string to operate on

  RETURNS:  number of chars replaced
__________________________________________________________________________ */

int check_input_length(char *str, char max_input_length);
/*
  ***** int check_input_length(char *str, char max_input_length) *****
  Compares length of string 'str'against reference max value 'max_input_length'

  REQUIRES:  max_input_length -> max reference value
             str              -> string to evaluate

  RETURNS:  0 -> if string length is less than maximum
            1 -> if string length is greater than  maximum
__________________________________________________________________________ */

int input_nonzero_int(char *str);
/*
  ***** int input_nonzero_int(char *str) *****
  Takes a number string and returns the integer equivalent.  NOTE*** an input
  value of zero is not distinguishable from non-number input and so is included
  in the error condition.  Also decimal values will be truncated in converting 
  to int.

  REQUIRES:  str -> number string to convert

  RETURNS:  0               -> if string is not a number or has zero value
            converted value -> if string is a number
__________________________________________________________________________ */

int print_file_line(char *name, int file_line);
/*
  ***** int printf_file_line(char *name, int file_line) *****
  Prints specified line 'file_line' from file 'name'

  REQUIRES:  file_line -> line to be printed
             name      -> file to print from

  RETURNS:  0 -> if successful
            1 -> if requested line is beyond length of file
__________________________________________________________________________ */

int search_file_delimited(char *name, char *delim_f, char *delim_b,
			  char *search);
/*
  ***** int search_file_delimited(char *name, char *delim_f, char *delim_b, char *search) *****
  Searches file 'name' delmited by front and back delimiters 'delim_f' and
  'delim_b' for occurance of string 'search.'  Prints delimited region which
  matches the search string at least once.

  REQUIRES:  delim_f -> front delimiter
             delim_b -> back delimiter
             search  -> term to search on
             name    -> name of file to search

  Returns:  0 -> if successful
            1 -> if search buffer overflows
            2 -> if requested file does not exist
__________________________________________________________________________ */

int getch(void);
/*
  ***** int getch(void) *****
  Obtains char from stdin without waiting for return key

  REQUIRES:  nothing

  RETURNS: ch -> entered character
__________________________________________________________________________ */

int rewind_line(char *print_string);
/*
  ***** int rewind_line(char *print_string) *****
  Prints srting 'print_string' then prompts and waits
  for any input and rewinds to the beginning of the line 
  erasing prompt and 'print_string'

REQUIRES: print_string -> string to print

RETURNS:  0
__________________________________________________________________________ */

int bash_resize(int x, int y);
/*
  ***** int bash_resize(int x, int y) *****
  Resizes bash window by system call.  NOTE: May only work
  with xterm emulator

  REQUIRES:  x -> desired window columns
             y -> desired window rows

  RETURNS:  0 -> no error checking

  USES: <stdlib.h>, <stdio.h>
__________________________________________________________________________ */

int print_table(int rows, int columns, int cell_size);
/*
  ***** print_talbe(int rows, int columns, int cell_size) *****
  prints a table to the screen of size 'rows' rows and 'columns'
  columns.  Each cell has a width of 'cell_size' characters

  REQUIRES:  cell_size -> size of each table cell in characters
             rows      -> number of rows in the table
             columns   -> number of columns in the table

  RETURNS:  0 -> no error checking

  USES:  <stdio.h>
__________________________________________________________________________ */

int check_file_for_string(char *name, char *str, int search_buffer_size);

int get_datestamp(char *str);


#endif				//UTIL_H_
