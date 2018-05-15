#include <stdio.h>
#include <string.h>

int extract_name(char *str);

int main()
{
    char file_buffer[1000];
    char tok_buffer[500];
    char file_char;
    int read_count = 0;
    char *tok;
    const char delim[2] = "$";
    FILE *fp;

    fp = fopen("brad.grp", "r");
    
    while((file_char = fgetc(fp)) != EOF)
    {
	file_buffer[read_count] = file_char;
	read_count++;
    }
    file_buffer[read_count + 1] = '\0';

    tok = strtok(file_buffer, delim);

    while(tok != NULL) {
//	printf("%s_____________________", tok);
	strcpy(tok_buffer, tok);
	extract_name(tok_buffer);
	tok = strtok(NULL, delim);
    }

    fclose(fp);

    return 0;
}

int extract_name(char *str)
{
    char *location;

    if((location = strstr(str, "name:")) != NULL) {
//	printf("\n");
	location += sizeof(char)*6;
	while(*location != '\n') {
	    putc(*location, stdout);
	    location += sizeof(char);
	}
//	printf("\n");
    }
    return 0;
}
