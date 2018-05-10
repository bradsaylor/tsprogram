#include <stdio.h>
#include <string.h>

#include "../include/tsp.h"
#include "../include/tsp_display.h"


int print_display_table(void)
{
     int count1 = 0;
     int count2 = 0;
     int count3 = 0;
     int pad_count = 0;
     int num_parameters = last - 1;

     //  populate display table with parameter attributes
     populate_display_table();

     //  print out top table horizontal delimiter
     print_table_horizontal_delimiter(num_param_attributes, table_cell_width);
     //  print '\n' to start first row
     printf("\n");

     //  loop through table rows and print out with '|' formatting
     for(count1 = 0; count1 < num_parameters; count1++){

	  //  print '|' delimiter to start table row
	  printf("|");

	  for(count2 = 0; count2 < num_param_attributes; count2++){

	       //  reset 'pad_count'
	       pad_count = 0;

	       //  determine number of padding spaces needed
	       pad_count = table_cell_width - strlen(display_table[count1][count2]);

	       //  pad the string with appropriate spaces
	       for(count3 = 0; count3 < pad_count; count3++){
		    strcat(display_table[count1][count2], " ");
	       }

	       //  print table cell
	       printf("%s", display_table[count1][count2]);

	       //  print '|' to delimit cell
	       printf("|");
	  }
	  //  print '\n' to begin new row
	  printf("\n");

	  //  print out row table horizontal delimiter
	  print_table_horizontal_delimiter(num_param_attributes, table_cell_width);

	  //  print '\n' to begin new row
	  printf("\n");
     }

  return 0;
}

int print_table_horizontal_delimiter(int columns, int cell_width)
{
     int count = 0;
     int width = columns * (cell_width + 1) + 1;

     for(count = 0; count < width; count++){
	  printf("_");
     }

     return 0;
}

int populate_display_table()
{
     int count1 = 0;
     int num_parameters = last - 1;

     for(count1 = 0; count1 < num_parameters; count1 ++){
	  strcpy(display_table[count1][0], parameters[count1 + 1].name);
	  strcpy(display_table[count1][1], parameters[count1 + 1].value);
	  strcpy(display_table[count1][2], parameters[count1 + 1].units);
	  strcpy(display_table[count1][3], parameters[count1 + 1].ref_value);
	  strcpy(display_table[count1][4], parameters[count1 + 1].variance);
	  strcpy(display_table[count1][5], parameters[count1 + 1].tolerance);
	  strcpy(display_table[count1][6], parameters[count1 + 1].fault);	  
     }

     return 0;
}
