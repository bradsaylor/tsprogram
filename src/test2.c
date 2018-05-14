#include <stdio.h>
#include <string.h>

int print_out(char *str);
int find_length(char *str);

int main()
{
    char my_str[] = "this is my string";

    print_out(my_str);
    printf("\n its is of size: %d\n", find_length(my_str));

    return 0;
}

int print_out(char *str)
{

    printf("\n%s\n", str);

    return 0;
}

int find_length(char *str)
{
    return (int)strlen(str);
}
