#include "./sort_file.h"

int main()
{
    // initialize name_array for dynamic allocation
    name_array = (char **)malloc(malloc_size);

    // open group file
    fp = fopen("brad.grp", "r");

    // read file into 'file_buffer'
    while((file_char = fgetc(fp)) != EOF)
    {
	file_buffer[read_count] = file_char;
	read_count++;
    }
    // append null char to 'file_buffer' for string operations
    file_buffer[read_count + 1] = '\0';

    // initialize strtok operation on 'file_buffer'
    tok = strtok(file_buffer, delim);

    // while more tokens exist in 'file_buffer'
    while(tok != NULL) {
	// copy tokenized portion to 'tok_buffer'
	strcpy(tok_buffer, tok);
	// extract name from tok_buffer store in 'current_name'
	extract_name(tok_buffer, current_name);
	// if 'current_name' is not empty
	if(strcmp(current_name, "")) {
	    // copy 'current_name' to 'name_array'
	    strcpy(name_array[malloc_size], current_name);
	    // increment 'malloc_size' for next dynamic allocation
	    malloc_size++;
	    // allocate one more *char to name_array
	    name_array = (char **) realloc(name_array, malloc_size);

	    for(count = 0; count < malloc_size; count++) {
		
	    }
	}
	// try to grab next token from 'file_buffer'
	tok = strtok(NULL, delim);
    }

    // close group file
    fclose(fp);

    for(int count = 0; count < malloc_size; count++) {
	printf("%s\n", name_array[count]);
    }
    printf("\n size is: %d\n", malloc_size);
    free(name_array);

    return 0;
}

int extract_name(char *str, char *current_name)
{
    char *location;
    int char_count = 0;

    // assign 'current_name' to empty string
    strcpy(current_name, "");
    
    // if "name:" exists in tok_buffer assign 'location' to its address
    if((location = strstr(str, "name:")) != NULL) {
	// increment address to skip over "name: "
	location += sizeof(char)*6;
	// read chars into 'current_name' until '\n' encountered
	while(*location != '\n') {
	    current_name[char_count] = *location;
	    // increment counter to keep track of 'current_array' index
	    char_count++;
	    // move 'location' ahead one char
	    location += sizeof(char);
	}
    }
    
    return 0;
}
