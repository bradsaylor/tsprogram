#include <stdio.h>
#include <string.h>

int return_file_as_string(char *name, char *file_str, int max_buffer_size);

int main ()
{
    char file_str[800];
    char file_name[] = "test.txt";
    int result;

    result = return_file_as_string(file_name, file_str,
			  sizeof(file_str)/sizeof(file_str[0]));

    if(!result) printf("%s\n", file_str);

    return 0;
}


int return_file_as_string(char *name, char *file_str, int max_buffer_size)
{
    FILE *fp;
    char file_buffer[max_buffer_size];
    int file_char;
    int read_count = 0;

    fp = fopen(name, "r");

    while((file_char = fgetc(fp)) != EOF)
    {
	file_buffer[read_count] = file_char;
	read_count++;
	if(read_count == (max_buffer_size - 2)) {
	    printf("buffer overflow\n");
	    return 1;
	}
    }
    file_buffer[read_count] = '\0';
    sprintf(file_str, "%s", file_buffer);
    
    return 0;
}
