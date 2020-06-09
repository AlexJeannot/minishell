#include "../includes/exec.h"

void ft_echo(char **args)
{
    int count;
    int option;

    count = 0;
    option = 0;
    if (args[count] && ft_strcmp(args[count], "-n") == 0)
    {
        while (ft_strcmp(args[count], "-n") == 0)
            count++;
        option = 1;
    }
    while (args[count])
    {
        //if (ft_strcmp(args[count], "$PWD") && pwd_check == 0)
         //   ft_putstr_fd(pwd_path, 1);
        ft_putstr_fd(args[count], 1);
        if (args[count + 1])
            write(1, " ", 1);
        count++;
    }
    if (!args[0] || !(option))
        write(1, "\n", 1);
}