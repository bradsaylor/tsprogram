#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char file_buffer[1000];
char tok_buffer[500];
char current_least_name[50];
char current_name[50];
char **name_array;

int read_count = 0;
int malloc_size = 0;
int count = 0;

char *tok;
char file_char;
const char delim[2] = "$";

FILE *fp;


int extract_name(char *str, char *current_name);
