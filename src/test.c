#include <stdio.h>
#include <string.h>

#include "../include/util.h"

int main()
{
    FILE *fp;
    char c = '\0';
    char read_buffer[1000];
    int read_count = 0;
    char str[20];

    strcpy(str, "target: Y");
    
    fp = fopen("test.txt", "r");

    c = fgetc(fp);
    while(c != EOF) {
	read_buffer[read_count] = c;
	read_count++;
	c = fgetc(fp);
    }
    read_buffer[read_count] = '\0';

    if(strstr(read_buffer, str) != NULL) {
	printf("\nfound it\n");
    } else printf("\ndidn't find it\n");

    fclose(fp);
    return 0;
}
