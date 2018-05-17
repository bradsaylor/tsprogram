#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "../include/menu_funcs.h"
#include "../include/tsp.h"
#include "../include/util.h"
#include "../include/tsp_file_func_utils.h"

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
    } else if (!strcmp(input, "m")) {
	target();
	return 0;
    } else if (!strcmp(input, "q")) {
	quit();
	return 0;
    } else if (!strcmp(input, "a")) {
	calc();
	return 0;
    } else
	return 1;


}

int menu(void)
{
    return 0;
}

int edit(int parameter_index)
{
    char new_value[MAX_VALUE_LENGTH];

    printf("Enter value for %s: ", parameters[parameter_index].name);
    fgets(new_value, sizeof(new_value), stdin);
    replace_char(new_value, 10, 0);
    //+1 to account for table header parameter
    strcpy(parameters[parameter_index + 1].value, new_value);

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

	strcpy(file_name, file_name_input);

	// if name is not blank set flag and exit loop
	for (count = 0; count < (int) strlen(file_name); count++) {
	    if (isalnum(file_name[count]))
		blank_name_check = 1;
	}
    }

    // replace ending line feed with string null termination
    replace_char(file_name, 10, 0);

    // replace any spaces or slashes with underscores
    // promp if you did
    if (replace_char(file_name, ' ', '_') ||
	replace_char(file_name, '/', '_') ||
	replace_char(file_name, '\\', '_')) {
	printf("\nReformatted to -> %s", file_name);
    }

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
    if(check_file_for_string(manifest_name, group_name, MAX_NAME_LENGTH * MAX_FILE_LENGTH) == 1) {
	append_to_file(manifest_name, group_name);
	new_group_flag = 1;
    }

    // if new file is group target check to see if group already has target
    if(is_target_flag.file_target == 'Y'){

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
		replace_file_string(
		    group_name_ext,	     target_search_string,
		    target_replace_with, MAX_FILE_LINE * MAX_FILE_LENGTH);
	    }
	}
    }

    append_parameter_data(group_name_ext, new_group_flag);

    sort_group_file(group_name_ext);

    return 0;
}

int open(void)
{
    char input[MAX_VALUE_LENGTH];
    char selection[MAX_VALUE_LENGTH];
    char open_group[MAX_NAME_LENGTH];
    int max_selection;
    FILE *fp_manifest;
    char group_name_ext[MAX_NAME_LENGTH + 3];


    // clear screen
    for (int count = 0; count < 50; count ++) printf("\n");

    // list group files in .grp manifest
    max_selection = list_file_numbered(manifest_name, MAX_FILE_LINE);
    printf("select group file: ");

    // prompt for an store user selection
    if(fgets(input, sizeof(selection), stdin) != NULL) {
	sscanf(input, "%s", selection);
    }

    // verify input is in allowable range
    if((atoi(selection) < 1) || (atoi(selection) > max_selection)) {
	rewind_line("Invalid input");
	return 1;
    }

    // read group file name from manifest file
    fp_manifest = fopen(manifest_name, "r");
    for(int count = 0; count < atoi(selection); count++) {
        fgets(open_group, MAX_FILE_LINE, fp_manifest);
    }
    fclose(fp_manifest);
    // replace ending '\n' with '\0'
    replace_char(open_group, 10, 0);

    // append .grp extension and store in 'group_name_ext'
    sprintf(group_name_ext, "%s%s", open_group, FILE_EXTENSION);

    printf("'%s'\n", group_name_ext);
    return 0;
}

int reference(void)
{

    return 0;
}

int tolerance(void)
{

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

int quit(void)
{

    return 0;
}

int calc(void)
{
    if (auto_calc_status == 'Y') auto_calc_status = 'N';
    else auto_calc_status = 'Y';

    return 0;
}


