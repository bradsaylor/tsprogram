#ifndef TSP_FILE_FUNC_UTILS_H_
#define TSP_FILE_FUNC_UTILS_H_

#include <stdio.h>

int append_parameter_data(char *name, int new_group_flag);
int sort_group_file(char *file_name);
int build_file_name_array(char *name, char ***name_array);
int extract_name(char *str, char *current_name);
int sort_names(char **name_array, int array_size);
int remove_file_from_group(char *file_to_remove, char *group);
int select_group_file(char *group_file_name);
int select_file(char *name, char ***name_array, int max_selection, char type);
int get_params_from_filestring(char *group_file_buffer, char *open_file, char type);
#endif //TSP_FILE_FUNC_UTILS_H_
