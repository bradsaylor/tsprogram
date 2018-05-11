#include <stdio.h>

#include "../include/util.h"

int main()
{
    int result = -1;

    result = check_file_for_string("test_file.txt", "brad", 1000);

    if(result == 0) {
	printf("\nfound\n");
    } else printf("\nnot found\n");

    return 0;
}
