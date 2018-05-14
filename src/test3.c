#include <stdio.h>
#include <string.h>

#include "../include/util.h"

int replace_file_string(char *name, char *old_str, char *new_str, int MAX_FILE_BUFFER);

int main ()
{
    char file_name[] = "test.txt";

    replace_file_string(file_name, "target: Y", "target: N", 500 * 100);

    return 0;
}

int replace_file_string(char *name, char* old_str, char *new_str, int MAX_FILE_BUFFER)
{
    char file_buffer[MAX_FILE_BUFFER];
    FILE *fp;
    char file_char = '\0';
    int read_count = 0;
    char *insert_point = NULL;
    char temp_file_name[] = ".temp_replace_file_string";

    fp = fopen(name, "r");
    file_char = fgetc(fp);

    while(file_char != EOF) {
	//  == MAX_FILE_BUFFER to allow for '\0'
	if (read_count == MAX_FILE_BUFFER) {
	    return 2;
	}
	file_buffer[read_count] = file_char;
	read_count++;
	file_char = fgetc(fp);
    }

    fclose(fp);
    
    file_buffer[read_count] = '\0';
    insert_point = strstr(file_buffer, old_str);
    if(insert_point == 0) {
	return 1;
    }

    fp = fopen(temp_file_name, "w");
    char *str_loc = file_buffer;
    while(str_loc < insert_point) {
	fputc(*str_loc, fp);
	str_loc += sizeof(char);
    }

    fprintf(fp, "%s", new_str);

    str_loc += sizeof(char) * ((int)strlen(old_str));
    while(*str_loc != '\0') {
	fputc(*str_loc, fp);
	str_loc += sizeof(char);
    }

    fclose(fp);

    rename(temp_file_name, name);
    remove(temp_file_name);

    return 0;
}
