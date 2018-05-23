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

int sort_group_file(char *file)
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

    elements_to_free = build_file_name_array(file, &name_array);
    malloc_size = elements_to_free;

    // sort name_array alphabetically ignore case
    sort_names(name_array, malloc_size);

    temp_file = fopen("temp_sort", "w");
    
    return_file_as_string(file, file_buffer, sizeof(file_buffer));
    
    // write out group file header
    strcpy(file_tokenized, file_buffer);
    tok = strtok(file_tokenized, delim);
    fprintf(temp_file, "%s", tok);

    // if current name matches tokenized section print to file
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

    remove(file);
    rename("temp_sort", file);

    return 0;
}

/********************************************
 ***** SORT_GROUP_FILE() UTILITIES
 ******************************************/
int build_file_name_array(char *name, char ***name_array)
{
    char file_tokenized[MAX_FILE_LINE * MAX_FILE_LENGTH];
    char file_buffer[MAX_FILE_LINE * MAX_FILE_LENGTH];    
    const char delim[2] = "$";
    char *tok;
    int malloc_size = 1;
    char tok_buffer[last * MAX_FILE_LINE];    
    char current_name[MAX_NAME_LENGTH];

    return_file_as_string(name, file_buffer, sizeof(file_buffer));
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

int remove_file_from_group(char *file_to_remove, char *group)
{
   char file_tokenized[MAX_FILE_LINE * MAX_FILE_LENGTH];
    char file_buffer[MAX_FILE_LINE * MAX_FILE_LENGTH];    
    const char delim[2] = "$";
    char *tok;
    char tok_buffer[last * MAX_FILE_LINE];    
    char current_name[MAX_NAME_LENGTH];
    int found_file_flag = 1;

    return_file_as_string(group, file_buffer, sizeof(file_buffer));
    strcpy(file_tokenized, file_buffer);
    
    // initialize strtok operation on 'file_buffer'
    tok = strtok(file_tokenized, delim);
    
    // while more tokens exist in 'file_buffer'
    while (tok != NULL) {
	// copy tokenized portion to 'tok_buffer'
	strcpy(tok_buffer, tok);
	// extract name from tok_buffer store in 'current_name'
	extract_name(tok_buffer, current_name);
	
	if (!strcmp(current_name, file_to_remove)) {
	    // delete file from group file
	    replace_file_string(group, tok_buffer, "", last * MAX_FILE_LINE);
	    found_file_flag = 0;
	}
	
	// try to grab next token from 'file_buffer'
	tok = strtok(NULL, delim);
    }

    return found_file_flag;    

}

int select_group_file(char *group_file_name)
{
    int max_selection = 0;
    char input[MAX_VALUE_LENGTH];
    char selection[MAX_VALUE_LENGTH];
    FILE *fp_manifest;    
    
    // list group files in .grp manifest
    max_selection = list_file_numbered(manifest_name, MAX_FILE_LINE);
    printf("select group file: ");

    // prompt for and store user selection
    if(fgets(input, sizeof(selection), stdin) != NULL) {
	sscanf(input, "%s", selection);
    }

    // verify input is in allowable range
    if((atoi(selection) < 1) || (atoi(selection) > max_selection)) {
	rewind_line("Invalid input", "...press any key");
	return 1;
    }

    // read group file name from manifest file
    fp_manifest = fopen(manifest_name, "r");
    for(int count = 0; count < atoi(selection); count++) {
        fgets(group_file_name, MAX_FILE_LINE, fp_manifest);
    }
    fclose(fp_manifest);
    
    // replace ending '\n' with '\0'
    replace_char(group_file_name, 10, 0);

    return 0;
}

int select_file(char *name, char *open_group, char ***name_array, int max_selection, char type)
{
    // types (open) -> o, (reference) -> r

    char input[MAX_VALUE_LENGTH];
    char selection[MAX_VALUE_LENGTH];
    int count = 0;
    int avg_select_number = -1;

    // list files
    for (count = 0; count < max_selection; count++) {
	printf("[%d] %s\n", count + 1, (*name_array)[count]);
    }

    // if loading a reference add "Group AVG" option
    if(type == 'r') printf("[%d] %s\n", count + 1, "Group AVG");

    // prompt for and store user selection
    printf("select file: ");
    if(fgets(input, sizeof(selection), stdin) != NULL) {
	sscanf(input, "%s", selection);
    }

    // if loading a reference increment max allowable selection
    // to account for "Group AVG" selection
    // Store index for "Group AVG" selection in 'avg_select_number'
    if(type == 'r') {
	max_selection++;
	avg_select_number = max_selection;
    }

    // verify input is in allowable range    
    if((atoi(selection) < 1) || (atoi(selection) > max_selection)) {
	rewind_line("Invalid input", "...press any key");
	return 1;
    }

    // if group avg is chosen set type to 'a'
    if(atoi(selection) == avg_select_number) type = 'a';
    
    // copy selected group or file to appropriate name variable
    if((type == 'o') || (type == 'r') || (type == 't'))
	strcpy(name, (*name_array)[atoi(selection) - 1]);
    else if(type == 'a') {
	char avg_group_file_name[MAX_NAME_LENGTH];
	strcpy(avg_group_file_name, open_group);
	strcat(avg_group_file_name, ".grp-AVG");
	strcpy(name, avg_group_file_name);
    }


    return type;
}

int get_params_from_filestring(char *group_file_buffer, char *open_file, char type)
{
    // types: (file) -> f, (reference) -> r, (average) -> a, (tolerance) -> t
    char group_file_tokenized[MAX_FILE_LINE * MAX_FILE_LENGTH];
    char *tok;
    const char delim[2] = "$";
    char current_name[MAX_NAME_LENGTH];
    char tok_buffer[last * MAX_FILE_LINE];
    float param_avg_array[last - 1];
    int avg_count = 0;
    
    // copy file buffer for tokenization
    strcpy(group_file_tokenized, group_file_buffer);

    // if taking avg and 'file_buffer contains 'empty_label' notify and abort
    if((type == 'a')&& (strstr(group_file_buffer, empty_label))) {
	rewind_line("group file contains incomplete data, aborting", "... any key to continue");
	return 1;
    }

    // initialize strtok operation on 'group_file_buffer'
    tok = strtok(group_file_tokenized, delim);

    // udpate global 'parameters' struct with new values
    while(tok != NULL) {
	strcpy(tok_buffer, tok);
	extract_name(tok_buffer, current_name);
	// if current tokenized chunk has a name
	if(strcmp(current_name, "")) {
	    avg_count++;
	    char search_string[MAX_VALUE_LENGTH];
	    char *location;
	    char extracted_value[MAX_VALUE_LENGTH];

	    for(int count = 2; count < last; count++) {
		strcpy(search_string, parameters[count].name);
		strcat(search_string, ":\t");
		location = strstr(tok_buffer, search_string);
		location += sizeof(char) * strlen(search_string);
		sscanf(location, "%s", extracted_value);
		switch(type) {
		case 'f':
		    if(!strcmp(current_name, open_file)) {
			strcpy(parameters[count].value, extracted_value);
		    }
		    break;
		case 'r':
		    if(!strcmp(current_name, open_file)) {			
			strcpy(parameters[count].ref_value, extracted_value);
		    }
		    break;
		case 'a':
		    // if current tokenized chunk is not a group target
		    if(!strstr(tok_buffer, "target:\tY")) {
		        param_avg_array[count - 2] += atof(extracted_value);
		    }
		    break;
		case 't':
		    if(!strcmp(current_name, open_file)) {
			strcpy(parameters[count].tolerance, extracted_value);
		    }
		    break;
		default:
		    break;
		}
	    }
	}	    
	tok = strtok(NULL, delim);
    }

    if(type == 'a') {
	char avg_value[MAX_VALUE_LENGTH];

	for(int count = 2; count < last; count++) {
	    sprintf(avg_value, "%f", param_avg_array[count - 2]/((float)(avg_count)));
	    strcpy(parameters[count].ref_value, avg_value);
	}
    }

    return 0;
}

int compile_variance()
{
  float variance_percent = 0;
  char variance_string[MAX_VALUE_LENGTH];
  
  
  for(int count = 2; count < last; count++) {
    // if parameter set has values for 'value' and 'ref_value'
    if((strcmp(parameters[count].value, empty_label)) && (strcmp(parameters[count].ref_value, empty_label))) {
      variance_percent =
	100 * (atof(parameters[count].value) - atof(parameters[count].ref_value))/(atof(parameters[count].ref_value));
      sprintf(variance_string, "%f", variance_percent);
      strcpy(parameters[count].variance, variance_string);
    } else strcpy(parameters[count].variance, empty_label);
  }

  return 0;
}

int load_tolerances(char *selected_tolerance)
{
    char tolerance_file_buffer[MAX_FILE_LINE * MAX_FILE_LENGTH];
    
    return_file_as_string(".tolerance_manifest", tolerance_file_buffer, sizeof(tolerance_file_buffer));
    get_params_from_filestring(tolerance_file_buffer, selected_tolerance, 't');

    return 0;
}
