#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/tsp_file_func_utils.h"
#include "../include/tsp.h"
#include "../include/util.h"

int append_parameter_data(char *name, int new_group_flag)
{
    int count = 0;

    //print group file header if this is a new group
    if(new_group_flag) {
	char group_id_string[MAX_NAME_LENGTH];
	sprintf(group_id_string, "%s %s", group_header_ID, group_name);
	append_to_file(name, group_id_string);
	append_to_file(name, "\n");
    }
	
    //print header rows to file
    append_to_file(name, "$");
    char name_string[MAX_NAME_LENGTH];
    sprintf(name_string, "%s\t%s", file_header_name, file_name);
    append_to_file(name, name_string);

    char date_string[MAX_NAME_LENGTH];
    get_datestamp(time_stamp);
    sprintf(date_string, "%s\t%s", file_header_date, time_stamp);
    append_to_file(name, date_string);

    char target_string[MAX_NAME_LENGTH];
    sprintf(target_string, "%s\t%c", file_header_target, is_target_flag.file_target);
    append_to_file(name, target_string);

    char parameter_attribute[MAX_VALUE_LENGTH];
    for(count = 2; count < last; count++) {
	sprintf(parameter_attribute, "%s:\t%s", parameters[count].name, parameters[count].value);
	append_to_file(name, parameter_attribute);
    }

    //finish by writing out a new line
    append_to_file(name, "");

    return 0;
}

int sort_group_file(char *file_name)
{
    char file_buffer[MAX_FILE_LINE * MAX_FILE_LENGTH];
    char file_tokenized[MAX_FILE_LINE * MAX_FILE_LENGTH];
    char tok_buffer[last * MAX_FILE_LINE];
    char current_name[MAX_NAME_LENGTH];
    char **name_array = NULL;
    int malloc_size = 1;
    int elements_to_free = 0;
    int count = 0;
    char *tok;
    const char delim[2] = "$";
    FILE *temp_file;

    return_file_as_string(file_name, file_buffer, sizeof(file_buffer));

    elements_to_free = build_file_name_array(&name_array, file_buffer);
    malloc_size = elements_to_free;

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

    // free allcoated 'name_array' elements and the array itself
    for (count = 0; count < elements_to_free; count++) {
	free(name_array[count]);
    }
    free(name_array);

    remove(file_name);
    rename("temp_sort", file_name);

    return 0;
}

/********************************************
 ***** SORT_GROUP_FILE() UTILITIES
 ******************************************/
int build_file_name_array(char ***name_array, char *file_buffer)
{
    char file_tokenized[MAX_FILE_LINE * MAX_FILE_LENGTH];
    const char delim[2] = "$";
    char *tok;
    int malloc_size = 1;
    char tok_buffer[last * MAX_FILE_LINE];    
    char current_name[MAX_NAME_LENGTH];
    
    strcpy(file_tokenized, file_buffer);
    
    // initialize strtok operation on 'file_buffer'
    tok = strtok(file_tokenized, delim);
    
    // initialize 'name_array' for dynamic allocation
    (*name_array) = malloc(malloc_size * sizeof(char *));
    (*name_array[0]) = malloc(MAX_NAME_LENGTH * sizeof(char));
    
    // while more tokens exist in 'file_buffer'
    while (tok != NULL) {
	// copy tokenized portion to 'tok_buffer'
	strcpy(tok_buffer, tok);
	// extract name from tok_buffer store in 'current_name'
	extract_name(tok_buffer, current_name);
	
	// if 'current_name' is not empty
	if (strcmp(current_name, "")) {
	    // copy 'current_name' to 'name_array'
	    strcpy((*name_array)[malloc_size - 1], current_name);
	    
	    // increment 'malloc_size' for next dynamic allocation
	    malloc_size++;
	    // allocate one more *char to name_array
	    (*name_array) = realloc((*name_array), malloc_size * sizeof(char *));
	    (*name_array)[malloc_size - 1] =
		malloc(MAX_NAME_LENGTH * sizeof(char));
	}
	
	// try to grab next token from 'file_buffer'
	tok = strtok(NULL, delim);
    }

    return malloc_size;
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
