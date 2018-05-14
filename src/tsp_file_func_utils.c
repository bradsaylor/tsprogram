#include <stdio.h>
#include <string.h>

#include "../include/tsp.h"
#include "../include/util.h"

int append_parameter_data(char *name)
{

    //print header rows to file
    char name_string[MAX_NAME_LENGTH];
    sprintf(name_string, "%s %s", file_header_name, file_name);
    append_to_file(name, name_string);

    char modified_string[MAX_NAME_LENGTH];
    get_datestamp(time_stamp);
    sprintf(modified_string, "%s %s", file_header_modified, time_stamp);
    append_to_file(name, modified_string);

    char target_string[MAX_NAME_LENGTH];
    sprintf(target_string, "%s %c", file_header_target, is_target_flag.file_target);
    append_to_file(name, target_string);

    return 0;
}
