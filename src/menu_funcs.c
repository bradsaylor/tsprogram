#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "../include/menu_funcs.h"
#include "../include/tsp.h"
#include "../include/util.h"
#include "../include/tsp_file_func_utils.h"
#include "../include/tsp_display.h"
#include "../include/init.h"

int validate_input(char *input)
{
    if (!strcmp(input, "")) {
	menu();
	return 0;
    } else if (!strcmp(input, "1")) {
	edit(atoi(input));
	return 0;
    } else if (!strcmp(input, "2")) {
	edit(atoi(input));
	return 0;
    } else if (!strcmp(input, "3")) {
	edit(atoi(input));
	return 0;
    } else if (!strcmp(input, "4")) {
	edit(atoi(input));
	return 0;
    } else if (!strcmp(input, "5")) {
	edit(atoi(input));
	return 0;
    } else if (!strcmp(input, "6")) {
	edit(atoi(input));
	return 0;
    } else if (!strcmp(input, "7")) {
	edit(atoi(input));
	return 0;
    } else if (!strcmp(input, "8")) {
	edit(atoi(input));
	return 0;
    } else if (!strcmp(input, "9")) {
	edit(atoi(input));
	return 0;
    } else if (!strcmp(input, "10")) {
	edit(atoi(input));
	return 0;
    } else if (!strcmp(input, "11")) {
	edit(atoi(input));
	return 0;
    } else if (!strcmp(input, "12")) {
	edit(atoi(input));
	return 0;
    } else if (!strcmp(input, "n")) {
	name();
	return 0;
    } else if (!strcmp(input, "g")) {
	group();
	return 0;
    } else if (!strcmp(input, "s")) {
	save();
	return 0;
    } else if (!strcmp(input, "o")) {
	open();
	return 0;
    } else if (!strcmp(input, "r")) {
	reference();
	return 0;
    } else if (!strcmp(input, "t")) {
	tolerance();
	return 0;
    } else if (!strcmp(input, "v")) {
	variance();
	return 0;
    } else if (!strcmp(input, "k")) {
	target();
	return 0;
    } else if (!strcmp(input, "q")) {
	return 1;
    } else if (!strcmp(input, "a")) {
	calc();
	return 0;
    } else if (!strcmp(input, "z")) {
	reset();
	return 0;
    } else {
        rewind_line("Not a menu function", "...press any key");
	return 0;
    }
}

int menu(void)
{
    char menu_line[MAX_FILE_LINE];
    FILE *fp;

    clear_screen();
    fp = fopen(menu_file, "r");
    while(fgets(menu_line, sizeof(menu_line), fp) != NULL) {
	printf("%s\n", menu_line);
    }
    printf("\n");

    return 0;
}

int edit(int parameter_index)
{
    int name_check = 0;
    
    char new_value[MAX_VALUE_LENGTH];
    if(!strcmp(file_name, empty_label)) name_check=name();
    if(name_check) return 1;

    printf("Enter value for %s: ", parameters[parameter_index + 1].name);
    fgets(new_value, sizeof(new_value), stdin);
    replace_char(new_value, 10, 0);
    //+1 to account for table header parameter
    strcpy(parameters[parameter_index + 1].value, new_value);

    file_saved_flag = NO;

    return 0;
}

int name(void)
{
    char file_name_input[MAX_NAME_LENGTH];
    int blank_name_check = 0;
    int count = 0;

    while (!blank_name_check) {
	printf("Enter file name: ");
	fgets(file_name_input, sizeof(file_name_input), stdin);

        if(!strcmp(file_name_input, "\n")) return 1;
	strcpy(file_name, file_name_input);
	
        // replace ending line feed with string null termination
        replace_char(file_name, 10, 0);

	// if name is not blank set flag and exit loop
	for (count = 0; count < (int) strlen(file_name); count++) {
	    if (isalnum(file_name[count]))
		blank_name_check = 1;
	}
    }

    // replace any spaces or slashes with underscores
    // promp if you did
    if (replace_char(file_name, ' ', '_') ||
	replace_char(file_name, '/', '_') ||
	replace_char(file_name, '\\', '_')) {
	printf("\nReformatted to -> %s", file_name);
    }

    file_saved_flag = NO;

    return 0;
}

int group(void)
{
   char  group_name_input[MAX_NAME_LENGTH];
    int blank_name_check = 0;
    int count = 0;

    while (!blank_name_check) {
	printf("Enter group name: ");
	fgets(group_name_input, sizeof(group_name_input), stdin);

	strcpy(group_name, group_name_input);

	// if name is not blank set flag and exit loop
	for (count = 0; count < (int) strlen(group_name); count++) {
	    if (isalnum(group_name[count]))
		blank_name_check = 1;
	}
    }

    // replace ending line feed with string null termination
    replace_char(group_name, 10, 0);

    // replace any spaces or slashes with underscores
    // promp if you did
    if (replace_char(group_name, ' ', '_') ||
	replace_char(group_name, '/', '_') ||
	replace_char(group_name, '\\', '_')) {
	printf("\nReformatted to -> %s", group_name);
    }

    return 0;
}

int save(void)
{
    int new_group_flag = 0;
    char group_name_ext[MAX_NAME_LENGTH + 3];

    //** Check to see if a name has been given
    //*** If not send to name() routine
    if (!strcmp(file_name, empty_label)) {
	name();
    }

    //** Check to see if a group name has been given
    //*** If not make a group name using file name
    if (!strcmp(group_name, empty_label)) {
	strcpy(group_name, file_name);
    }

    // string to hold group file name with file extension
    sprintf(group_name_ext, "%s%s", group_name, FILE_EXTENSION);

    //  Check .grp manifest file to see if group name exists
    //  if not then add it and set new group flag
    if(check_file_for_string(manifest_name, group_name,
			     MAX_NAME_LENGTH * MAX_FILE_LENGTH) == 1) {
	append_to_file(manifest_name, group_name);
	new_group_flag = 1;
    }

    
    if(!new_group_flag){
        // Check to see if the .grp file has a file with this name
	// prompt to overwrite if no abort save
	char **name_array;
	int elements_to_free = 0;
	int overwrite_response = 0;
	// build array of file names in .grp file store in 'name_array'
	elements_to_free = build_file_name_array(group_name_ext, &name_array);
	for(int count = 0; count < (elements_to_free - 1); count++) {
	    // if file name found to already exist in .grp file
	    if(!strcmp(name_array[count], file_name)) {
		overwrite_response = rewind_line("File already exists overwite?", "...[y]es, [n]o");
		if((overwrite_response != 'y') && (overwrite_response != 'n')){
		    rewind_line("Invalid input aborting save", "...press any key");
		}
		if(overwrite_response == 'n') return 1;
		else {
		    // if response not NO remove the file from the group file
		    remove_file_from_group(file_name, group_name_ext);
		}
	    }
	}
	// free 'name_array' elements and 'name_array' itself
        for(int count = 0; count < elements_to_free; count++) {
	    free(name_array[count]);
        }
        free(name_array);
    }
    

    // if new file is group target check to see if group already has target
    if(is_target_flag.file_target == 'Y'){

	// assemble string to search, and string to replace with
	// + 3 to add space for '<SPC>' 'Y' and '\0'
	char target_search_string[(int)strlen(file_header_target + 3)];
	char target_replace_with[(int)strlen(file_header_target + 3)];
	strcpy(target_search_string, file_header_target);
	strcat(target_search_string, "\tY");
	strcpy(target_replace_with, file_header_target);
	strcat(target_replace_with, "\tN");

        // if not a new group file
	// if target Y string exits in file then re-write with target N string
	// use while in case there are multiple target Y strings

	if(!new_group_flag) {
	    while(check_file_for_string(group_name_ext, target_search_string,
					MAX_FILE_LINE * MAX_FILE_LENGTH) == 0){
		replace_file_string(group_name_ext, target_search_string,
		                    target_replace_with, MAX_FILE_LINE * MAX_FILE_LENGTH);
	    }
	}
    }


    append_parameter_data(group_name_ext, new_group_flag);

    sort_group_file(group_name_ext);

    file_saved_flag = YES;

    return 0;
}

int open(void)
{
    char open_group[MAX_NAME_LENGTH];
    char open_file[MAX_NAME_LENGTH];
    int max_selection;
    char group_name_ext[MAX_NAME_LENGTH + 3];
    char **name_array;
    char group_file_buffer[MAX_FILE_LINE * MAX_FILE_LENGTH];
    int elements_to_free = 0;

    // if there are no group files output error and return
    if(count_file_lines(manifest_name, MAX_FILE_LINE) < 1) {

	rewind_line("No .grp files to open", "...press any key");
	return 1;
    }    

    // prompt to save current file if unsaved
    if(!file_saved_flag) {
	char save_response;
	
	save_response = rewind_line("Save current file?", "...[y]es, [n]o");
	if((save_response != 'y') && (save_response != 'n')) {
	    rewind_line("Invalid input, aborting open", "...press any key");
	} else {
	    if(save_response == 'y') save();
	}
    }

    // clear screen
    clear_screen();

    if(select_group_file(open_group)) return 1;

    // append .grp extension and store in 'group_name_ext'
    sprintf(group_name_ext, "%s%s", open_group, FILE_EXTENSION);

    // create 'group_file_buffer' to store group file as string
    return_file_as_string(group_name_ext, group_file_buffer, sizeof(group_file_buffer));
    
    // build 'name_array' to hold all names in chosen group file
    elements_to_free = build_file_name_array(group_name_ext, &name_array);
    max_selection = elements_to_free - 1;   

    // clear screen
    clear_screen();

    if(select_file(open_file, open_group, &name_array, max_selection, 'o') == 'x') return 1;

    get_params_from_filestring(group_file_buffer, open_file, 'f');

    /* update global vars 'group_name' and 'file_name' */
    /* with selected values */
    strcpy(group_name, open_group);
    strcpy(file_name, open_file);

    // free 'name_array' elements and 'name_array' itself
    for(int count = 0; count < elements_to_free; count++) {
	free(name_array[count]);
    }
    free(name_array);

    return 0;
}

int reference(void)
{
    char open_group[MAX_NAME_LENGTH];
    char open_file[MAX_NAME_LENGTH];
    char group_name_ext[MAX_NAME_LENGTH + 3];
    char **name_array;
    char group_file_buffer[MAX_FILE_LINE * MAX_FILE_LENGTH];
    int elements_to_free = 0;
    char file_type = 0;
    int params_obtained_flag = 0;

    // clear screen
    clear_screen();

    if(select_group_file(open_group)) return 1;

    // append .grp extension and store in 'group_name_ext'
    sprintf(group_name_ext, "%s%s", open_group, FILE_EXTENSION);

    return_file_as_string(group_name_ext, group_file_buffer, sizeof(group_file_buffer));
    elements_to_free = build_file_name_array(group_name_ext, &name_array);

    // clear screen
    clear_screen();
    
    file_type = select_file(open_file, open_group, &name_array, elements_to_free - 1, 'r');
    if(file_type == 'x') return 1;

    params_obtained_flag = get_params_from_filestring(group_file_buffer, open_file, file_type);

    /* update global vars 'group_name' and 'file_name' */
    /* with selected values */
    if(!params_obtained_flag) {
        strcpy(ref_group_name, open_group);
        strcpy(ref_file_name, open_file);
    }

    // free 'name_array' elements and 'name_array' itself
    for(int count = 0; count < elements_to_free; count++) {
	free(name_array[count]);
    }
    free(name_array);

    return 0;
}

int tolerance(void)
{
    char **name_array;
    int elements_to_free = 0;
    char selected_tolerance[MAX_NAME_LENGTH];
    int max_selection = 0;



    elements_to_free = build_file_name_array(".tolerance_manifest", &name_array);
    max_selection = elements_to_free - 1;
    select_file(selected_tolerance, "", &name_array, max_selection, 't');
    load_tolerances(selected_tolerance);

    
    return 0;
}

int variance(void)
{

    return 0;
}

int target(void)
{
    if(is_target_flag.file_target == 'N') is_target_flag.file_target = 'Y';
    else is_target_flag.file_target = 'N';

    return 0;
}

int calc(void)
{
    if (auto_calc_status == 'Y') auto_calc_status = 'N';
    else auto_calc_status = 'Y';

    return 0;
}

int reset(void)
{
    tsp_init();
    
    return 0;
}
