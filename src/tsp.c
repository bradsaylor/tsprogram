#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/tsp.h"

// include utilities and init headers
#include "../include/util.h"
#include "../include/init.h"
#include "../include/menu_funcs.h"
#include "../include/debug.h"
#include "../include/tsp_display.h"

// 'last+1' to include display table header
struct parameter parameters[last + 1];
struct is_target is_target_flag;

char file_name[MAX_NAME_LENGTH];
char group_name[MAX_NAME_LENGTH];
char manifest_name[] = ".grp_manifest";
char auto_calc_status;
char time_stamp[50];

//  string constants to define file header information
char file_header_name[]		= "name:";
char file_header_date[]		= "date:";
char file_header_target[]	= "target:";
char group_header_ID[]		= "ID:";

// global flag definitions
int file_saved_flag = YES;


int main(void)
{
    // local variables
    char input[MAX_VALUE_LENGTH];
    char selection[MAX_VALUE_LENGTH];

    // run initialization function
    tsp_init();

    while (1) {
	// print initial screen
	print_display_table();

	//prompt for input
	printf("Make selection: ");

	// read input and scan into string if size is ok
	if (fgets(input, sizeof(selection), stdin) != NULL) {
	    sscanf(input, "%s", selection);
	}
	if (!strcmp(selection, "q"))
	    return 0;

	// validate input
	if (validate_input(selection))
	    rewind_line("Not a menu function", "...press any key");
    }
    return 0;

}
