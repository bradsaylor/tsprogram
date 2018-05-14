#include <stdio.h>
#include <string.h>

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
    append_to_file(name, "\n");

    return 0;
}
