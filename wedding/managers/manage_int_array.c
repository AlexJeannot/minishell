#include "../includes/exec.h"

int int_array_length(int *input_array)
{
    int count;

    count = 0;
    if (input_array)
        while (input_array[count] != -1)
            count++;
    else
        return (KO);
    return (count);
}

void display_int_array(int *input_array)
{
    int count;

    count = 0;
    while (input_array[count] != -1)
    {
        ft_putnbr(input_array[count]);
        write(1, "\n", 1);
        count++;
    }
}

void free_int_array(int *input_array)
{
    if (input_array)
    {
        free(input_array);
        input_array = NULL;
    }
}