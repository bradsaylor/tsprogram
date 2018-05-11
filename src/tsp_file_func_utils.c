#include <stdio.h>
#include <string.h>

#include "../include/tsp.h"
#include "../include/util.h"

int insert_parameter_data(int new_group_flag)
{
    int file_line_count = 0;
    int insert_point = 0;
    int copied_counter = 0;
    FILE *fp_group_file;
    char copied_from_file[MAX_FILE_LENGTH][MAX_NAME_LENGTH];
    char file_line[MAX_FILE_LINE];
    char parsed_name[MAX_NAME_LENGTH];
    char parsed_value[MAX_NAME_LENGTH];

    //** Open file
    char group_name_ext[MAX_NAME_LENGTH + 3];
    sprintf(group_name_ext, "%s%s", group_name, FILE_EXTENSION);
    fp_group_file = fopen(group_name_ext, "a+");

    //** Check to see if file size plus pending data will exceed limit
    //*** If so display error and exit back to main()
    if (check_file_length(group_name, 1000, 300)) {
	fclose(fp_group_file);
	printf("\nFile length too long exceeds %d lines\n",
	       MAX_FILE_LENGTH);
	return 1;
    }
    //  ** If target flag is set then re-write file replacing any "ref: Y" with "ref: N"

    //** Search through .grp file to find alphabetic insert point
    //*** If found start caching existing file lines and writing out data
    //**** When data write is finished append a blank line
    //**** Write out the cached data appended below the blank line
    //*** If not found append data to end of file

    // Determine insert point:  grab line from file while insert point not found
    while (fgets(file_line, MAX_FILE_LINE, fp_group_file) != NULL) {
	
	file_line_count++;

	// sscanf returns EOF if scan is not successful i.e. when reading a blank line
	if (sscanf(file_line, "%s %s", parsed_name, parsed_value) != EOF) {
	        
	    //  if insert point not found compare 'file_name' to current name from file      
	    if (insert_point == 0) {
		
		if (!strcmp(parsed_name, "name:")) {
		    //  if name from file is after 'file_name' in alphabet
		    if (strcmp(parsed_value, file_name) > 0) {
			//  set 'insert_point' to this line
			insert_point = file_line_count;
		    }
		}
	    }
	    
	    //  if insert point has been found
	    if(insert_point != 0) {
		//  copy current file line in to 'copied_from_file' buffer
		strcpy(copied_from_file[copied_counter], file_line);
		//  keep track of how many lines have been buffered so far
		copied_counter++;
		//  write out next parameter data
		//  first write header information
		//  next write out parameter data "name [tab] value"
		//  last write a delimiting '\n'
            }
	}
    }

    fclose(fp_group_file);

    return 0;
}
