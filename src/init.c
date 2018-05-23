#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "../include/init.h"
#include "../include/tsp.h"
#include "../include/tsp_file_func_utils.h"

int tsp_init(void)
{

    strcpy(parameters[table_header].name, "Name");
    strcpy(parameters[table_header].value, "Value");
    strcpy(parameters[table_header].units, "Units");
    strcpy(parameters[table_header].ref_value, "Ref. Value");
    strcpy(parameters[table_header].variance, "Variance");
    strcpy(parameters[table_header].tolerance, "Tolerance");
    strcpy(parameters[table_header].fault, "Fault");


    strcpy(parameters[fs].name, "fs");
    strcpy(parameters[fs].value, empty_label);
    strcpy(parameters[fs].units, "Hz");
    strcpy(parameters[fs].ref_value, empty_label);
    strcpy(parameters[fs].variance, empty_label);
    strcpy(parameters[fs].tolerance, empty_label);
    strcpy(parameters[fs].fault, empty_label);


    strcpy(parameters[re].name, "re");
    strcpy(parameters[re].value, empty_label);
    strcpy(parameters[re].units, "Ohms");
    strcpy(parameters[re].ref_value, empty_label);
    strcpy(parameters[re].variance, empty_label);
    strcpy(parameters[re].tolerance, empty_label);
    strcpy(parameters[re].fault, empty_label);


    strcpy(parameters[res].name, "res");
    strcpy(parameters[res].value, empty_label);
    strcpy(parameters[res].units, "Ohms");
    strcpy(parameters[res].ref_value, empty_label);
    strcpy(parameters[res].variance, empty_label);
    strcpy(parameters[res].tolerance, empty_label);
    strcpy(parameters[res].fault, empty_label);


    strcpy(parameters[qms].name, "qms");
    strcpy(parameters[qms].value, empty_label);
    strcpy(parameters[qms].units, "");
    strcpy(parameters[qms].ref_value, empty_label);
    strcpy(parameters[qms].variance, empty_label);
    strcpy(parameters[qms].tolerance, empty_label);
    strcpy(parameters[qms].fault, empty_label);


    strcpy(parameters[qes].name, "qes");
    strcpy(parameters[qes].value, empty_label);
    strcpy(parameters[qes].units, "");
    strcpy(parameters[qes].ref_value, empty_label);
    strcpy(parameters[qes].variance, empty_label);
    strcpy(parameters[qes].tolerance, empty_label);
    strcpy(parameters[qes].fault, empty_label);


    strcpy(parameters[qts].name, "qts");
    strcpy(parameters[qts].value, empty_label);
    strcpy(parameters[qts].units, "");
    strcpy(parameters[qts].ref_value, empty_label);
    strcpy(parameters[qts].variance, empty_label);
    strcpy(parameters[qts].tolerance, empty_label);
    strcpy(parameters[qts].fault, empty_label);


    strcpy(parameters[vas].name, "vas");
    strcpy(parameters[vas].value, empty_label);
    strcpy(parameters[vas].units, "Litres");
    strcpy(parameters[vas].ref_value, empty_label);
    strcpy(parameters[vas].variance, empty_label);
    strcpy(parameters[vas].tolerance, empty_label);
    strcpy(parameters[vas].fault, empty_label);


    strcpy(parameters[mms].name, "mms");
    strcpy(parameters[mms].value, empty_label);
    strcpy(parameters[mms].units, "Grams");
    strcpy(parameters[mms].ref_value, empty_label);
    strcpy(parameters[mms].variance, empty_label);
    strcpy(parameters[mms].tolerance, empty_label);
    strcpy(parameters[mms].fault, empty_label);


    strcpy(parameters[cms].name, "cms");
    strcpy(parameters[cms].value, empty_label);
    strcpy(parameters[cms].units, "um/N");
    strcpy(parameters[cms].ref_value, empty_label);
    strcpy(parameters[cms].variance, empty_label);
    strcpy(parameters[cms].tolerance, empty_label);
    strcpy(parameters[cms].fault, empty_label);


    strcpy(parameters[bl].name, "bl");
    strcpy(parameters[bl].value, empty_label);
    strcpy(parameters[bl].units, "Tm");
    strcpy(parameters[bl].ref_value, empty_label);
    strcpy(parameters[bl].variance, empty_label);
    strcpy(parameters[bl].tolerance, empty_label);
    strcpy(parameters[bl].fault, empty_label);


    strcpy(parameters[spl].name, "spl");
    strcpy(parameters[spl].value, empty_label);
    strcpy(parameters[spl].units, "dBSPL");
    strcpy(parameters[spl].ref_value, empty_label);
    strcpy(parameters[spl].variance, empty_label);
    strcpy(parameters[spl].tolerance, empty_label);
    strcpy(parameters[spl].fault, empty_label);


    strcpy(parameters[sd].name, "sd");
    strcpy(parameters[sd].value, empty_label);
    strcpy(parameters[sd].units, "cm^2");
    strcpy(parameters[sd].ref_value, empty_label);
    strcpy(parameters[sd].variance, empty_label);
    strcpy(parameters[sd].tolerance, empty_label);
    strcpy(parameters[sd].fault, empty_label);

    strcpy(file_name, empty_label);
    strcpy(ref_file_name, empty_label);
    strcpy(group_name, empty_label);
    strcpy(ref_group_name, empty_label);
    strcpy(tolerance_name, "default");
    auto_calc_status = 'N';

    //  check to see if .grp manifest file has been created
    //  if not then create it
    if(access(manifest_name, F_OK) == -1) {
	FILE *fp = fopen(manifest_name, "w");
	fclose(fp);
    }

    is_target_flag.file_target = 'N';
    is_target_flag.ref_target = 'N';

    // load tolerance table
    load_tolerances("default");

    return 0;

}
