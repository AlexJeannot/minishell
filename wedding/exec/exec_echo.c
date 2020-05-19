#include "../includes/exec.h"

void ft_echo(char **args)
{
    int count;

    count = 0;
    if (args[0] && ft_strcmp(args[0], "-n") == 0)
        count = 1;
    while (args[count])
    {
        ft_putstr_fd(args[count], 1);
        if (args[count + 1])
            write(1, " ", 1);
        count++;
    }
    if (!args[0] || ft_strcmp(args[0], "-n") != 0)
        write(1, "\n", 1);
}