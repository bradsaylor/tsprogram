#include <stdio.h>
#include <string.h>

#include "../include/util.h"

int replace_file_line(char *name, int file_line, char *new_str);
int get_file_line(char *name, char *str);

int main ()
{
    char file_name[] = "test.txt";
    int line_to_replace = 0;

    line_to_replace = get_file_line(file_name, "target: Y");
    replace_file_line(file_name, line_to_replace, "target: N");

    return 0;
}

int get_flie_line(char *name, char *str)
{
    int matching_line = 0;
    int line_count = 0;
    char file_line[1000];
    FILE *fp;

    fp = fopen(name, "r");

    while (fgets(file_line, sizeof(file_line), fp) != NULL) {
	line_count++;
	if(!strcmp(file_line, str)) {
	    matching_line = line_count;
	    return matching_line;
	}
    }

    fclose(fp);
    
    return -1;    
}

int replace_file_line(char *name, int file_line, char *new_str)
{
    char line[1000];
    FILE *fp;
    int line_count = 0;

    if(count_file_lines(name, 100) < file_line) {
	printf("\nrequested line does not exist\n");
	return 2;
    }

    fp = fopen(name, "r+");
    
    while(fgets(line, sizeof(file_line), fp) != NULL) {
	line_count++;
	if(line_count == (file_line - 1)) {
	    fprintf(fp, "%s\n", new_str);
	    fclose(fp);
	    return 0;
	}
    }

    return 1;
}
