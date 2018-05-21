#include "../include/sort_file.h"
#include "../include/util.h"

int main()
{
     // initialize name_array for dynamic allocation
    name_array = malloc(malloc_size * sizeof(char *));
    name_array[0] = malloc(MAX_NAME_LENGTH * sizeof(char));

    // open group file
    fp = fopen("brad.grp", "r");

    // read file into 'file_buffer'
    while ((file_char = fgetc(fp)) != EOF) {
	file_buffer[read_count] = file_char;
	read_count++;
    }

    // append null char to 'file_buffer' for string operations
    file_buffer[read_count + 1] = '\0';
    strcpy(file_tokenized, file_buffer);


    // initialize strtok operation on 'file_buffer'
    tok = strtok(file_tokenized, delim);

    // while more tokens exist in 'file_buffer'
    while (tok != NULL) {
	// copy tokenized portion to 'tok_buffer'
	strcpy(tok_buffer, tok);
	// extract name from tok_buffer store in 'current_name'
	extract_name(tok_buffer, current_name);
	
	// if 'current_name' is not empty
	if (strcmp(current_name, "")) {
	    // copy 'current_name' to 'name_array'
	    strcpy(name_array[malloc_size - 1], current_name);
	    // increment 'malloc_size' for next dynamic allocation
	    malloc_size++;
	    // allocate one more *char to name_array
	    name_array = realloc(name_array, malloc_size * sizeof(char *));
	    name_array[malloc_size - 1] =
		malloc(MAX_NAME_LENGTH * sizeof(char));
	}
	
	// try to grab next token from 'file_buffer'
	tok = strtok(NULL, delim);
    }

    // close group file
    fclose(fp);

/*    for (int count = 0; count < malloc_size - 1; count++) {
	printf("%s\n", name_array[count]);
    }
    printf("\n");
*/

    // sort name_array alphabetically ignore case
    sort_names(name_array, malloc_size);

    temp_file = fopen("temp_sort", "w");

    // write out group file header
    strcpy(file_tokenized, file_buffer);
    tok = strtok(file_tokenized, delim);
    fprintf(temp_file, "%s", tok);

    for(count = 0; count < malloc_size; count++) {
        // initialize strtok operation on 'file_buffer'
        strcpy(file_tokenized, file_buffer);
        tok = strtok(file_tokenized, delim);

	while(tok != NULL) {
	    strcpy(tok_buffer, tok);
	    extract_name(tok_buffer, current_name);
	    if(strcmp(current_name, "")) {
		if(!strcmp(current_name, name_array[count])) {
		    fprintf(temp_file,"$");
		    fprintf(temp_file, "%s", tok_buffer);
		}
	    }	    
	    tok = strtok(NULL, delim);
	}
    }
    fclose(temp_file);

/*    for (int count = 0; count < malloc_size - 1; count++) {
	printf("%s\n", name_array[count]);
    }
*/
    // free allcoated 'name_array' elements and the array itself
    for (count = 0; count < malloc_size; count++) {
	free(name_array[count]);
    }
    free(name_array);

    return 0;
}

int extract_name(char *str, char *current_name)
{
    char *location;
    int char_count = 0;

    // if "name:" exists in tok_buffer assign 'location' to its address
    if ((location = strstr(str, "name:")) != NULL) {
	// increment address to skip over "name: "
	location += sizeof(char) * 6;
	// read chars into 'current_name' until '\n' encountered
	while (*location != '\n') {
	    current_name[char_count] = *location;
	    // increment counter to keep track of 'current_array' index
	    char_count++;
	    // move 'location' ahead one char
	    location += sizeof(char);
	}
	// terminate 'current_name' with null char for string operations
	current_name[char_count] = '\0';
    }else current_name[char_count] = '\0';

    return 0;
}

int sort_names(char **name_array, int array_size)
{
    int made_change_flag = 1;
    int count = 0;
    char temp[MAX_NAME_LENGTH];

    while(made_change_flag) {
	made_change_flag = 0;
	for(count = 0; count < (array_size - 1); count++) {
	    if(strcmp_no_case(name_array[count], name_array[count + 1]) > 0) {
		strcpy(temp, name_array[count]);
		strcpy(name_array[count], name_array[count + 1]);
		strcpy(name_array[count + 1] ,temp);
		made_change_flag = 1;
	    }
	}
    }

    return 0;
}
