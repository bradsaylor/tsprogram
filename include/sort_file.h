#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 40

char file_buffer[1000];
char file_tokenized[1000];
char tok_buffer[500];
char current_least_name[50];
char current_name[50];
char **name_array;
char *file_string;

int read_count = 0;
int malloc_size = 1;
int count = 0;

char *tok;
int file_char;
const char delim[2] = "$";

FILE *fp;
FILE *temp_file;

int extract_name(char *str, char *current_name);

int sort_names(char **name_array, int array_size);
