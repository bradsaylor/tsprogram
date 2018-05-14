#include <stdio.h>
#include <string.h>

#include "../include/tsp.h"
#include "../include/util.h"

int append_parameter_data(char *name)
{

    //print header rows to file
    char name_string[MAX_NAME_LENGTH];
    strcpy(name_string, file_header_name);
    strcat(name_string, file_name);
    append_to_file(name, name_string);

    char modified_string[MAX_NAME_LENGTH];
    strcpy(modified_string, file_header_name);
    strcat(modified_string, file_name);
    append_to_file(name, modified_string);

    char target_string[MAX_NAME_LENGTH];
    strcpy(target_string, file_header_name);
    strcat(target_string, file_name);
    append_to_file(name, target_string);

    return 0;
}
