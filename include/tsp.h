#ifndef TSP_H_
#define TSP_H_


/******************************
  global constant declarations
*******************************/
#define MAX_NAME_LENGTH 50	       // max length of any string input
#define MAX_VALUE_LENGTH 15	       // max length of any number input
#define MAX_FILE_LINE 100	       // max chars in any file line
#define MAX_FILE_LENGTH 500	       // max number of lines in any file
#define FILE_EXTENSION ".grp"	       // extension for group data files
#define LINES_PER_WRITE 15	       // DON'T KNOW!!! SHOULD BE RESOLVED OR
				// DELETED
#define empty_label "****"	       // label for use to display non-entered
				// strings
#define table_cell_width 15	       // cell width in chars of output table
#define num_param_attributes 7	       // number of attributes for each parameter
				// struct
#define lines_to_clear_scrn 50		// lines printed in clear_screen() fn
#define YES 1				
#define NO 0

/******************************
  global data structures
******************************/
struct parameter {		// parameter struct to hold param
    // attributes
    char name[MAX_VALUE_LENGTH];
    char value[MAX_VALUE_LENGTH];
    char units[MAX_VALUE_LENGTH];
    char ref_value[MAX_VALUE_LENGTH];
    char variance[MAX_VALUE_LENGTH];
    char tolerance[MAX_VALUE_LENGTH];
    char fault[MAX_VALUE_LENGTH];
};

struct is_target {		
    char file_target;
    char  ref_target;
};


/******************************
  global enums
******************************/
enum parameter_list		// enum to reference parameters as
				// integers
{
    table_header = 1,
    fs,
    re,
    res,
    qms,
    qes,
    qts,
    vas,
    mms,
    cms,
    bl,
    spl,
    sd,
    last,			       // 'last' used to indicate total number of 
    // parameters
};


/******************************
  global variable declarations
******************************/
extern struct parameter parameters[];	// array of paramters defined in
					// tsp.c
extern struct is_target is_target_flag;	// target flag for file and ref
					
extern char file_name[];	// data file name defined in tsp.c
extern char ref_file_name[];	// reference data file name defined in tsp.c
extern char group_name[];	// group file name defined in tsp.c
extern char ref_group_name[];	// reference group file name defined in tsp.c
extern char tolerance_name[];	// name of selected tolerance file defined in tsp.c
extern char manifest_name[];	// .grp file manifest file name
extern char menu_file[];	// name of menu definition file
extern char logo_file[];	// name of splash screen logo data file
extern char auto_calc_status;
extern char time_stamp[];

//  output table char array
	// 'last - 1' -> number of parameters including table header
	// 'table_cell_width + 1' -> width of table cell plus '\0'
	// terminator
char display_table[last - 1][num_param_attributes][table_cell_width + 1];

//  string constants to define file header information
extern char file_header_name[];
extern char file_header_date[];
extern char file_header_target[];

// string constants to define group file header information
extern char group_header_ID[];
extern int file_saved_flag;

#endif				// TSP_H_
