#ifndef TSP_FILE_FUNC_UTILS_H_
#define TSP_FILE_FUNC_UTILS_H_

#include <stdio.h>

int append_parameter_data(char *name, int new_group_flag);
int sort_group_file(char *file_name);
int build_file_name_array(char ***name_array, char *file_buffer);
int extract_name(char *str, char *current_name);
int sort_names(char **name_array, int array_size);

#endif //TSP_FILE_FUNC_UTILS_H_
