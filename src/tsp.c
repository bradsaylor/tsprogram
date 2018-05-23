#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/tsp.h"

// include utilities and init headers
#include "../include/util.h"
#include "../include/init.h"
#include "../include/menu_funcs.h"
#include "../include/tsp_file_func_utils.h"
#include "../include/debug.h"
#include "../include/tsp_display.h"

// 'last+1' to include display table header
struct parameter parameters[last + 1];
struct is_target is_target_flag;

char file_name[MAX_NAME_LENGTH];
char ref_file_name[MAX_NAME_LENGTH];
char group_name[MAX_NAME_LENGTH];
char ref_group_name[MAX_NAME_LENGTH];
char tolerance_name[MAX_NAME_LENGTH];
char manifest_name[] = ".grp_manifest";
char menu_file[] = ".menu";
char logo_file[] = ".logo";
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
    int quit_flag = 0;
    int screen_width = (table_cell_width + 1) * num_param_attributes + 2;
    int screen_height = (2 * (last - 1) + 1) + 6;

    // run initialization function
    tsp_init();

    bash_resize(screen_width, screen_height);

    splash_screen();

    while (!quit_flag) {
        // compile variance data
        compile_variance();

	// compute faults
	compute_faults();
        
      
	// print initial screen
	print_display_table();

	//prompt for input
	printf("[m]->menu\n");
	printf("Make selection: ");

	// read input and scan into string if size is ok
	if (fgets(input, sizeof(selection), stdin) != NULL) {
	    sscanf(input, "%s", selection);
	}

	while(!strcmp(selection, "m"))
	{
	    menu();
	    printf("Make selection: ");

	    // read input and scan into string if size is ok
	    if (fgets(input, sizeof(selection), stdin) != NULL) {
	        sscanf(input, "%s", selection);
	    }	    
	}

	// set quit input
	if (!strcmp(selection, "q")) {
	    clear_screen();
	    return 0;
	}

	// validate input
	validate_input(selection);
    }
    return 0;

}
