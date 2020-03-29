#include "../includes/minishell.h"

void display_exec(char *exec)
{
    write(1, exec, ft_strlen(exec));
    write(1, ": ", 2);
}

void display_error(char *exec, char *error_str)
{
    char *sys_error;

    write(1, "Minishell: ", 11);
    if (exec)
        display_exec(exec);
    if (error_str)
        write(1, error_str, ft_strlen(error_str));
    else
    {
        sys_error = strerror(errno);
        write(1, sys_error, ft_strlen(sys_error));
    }
    write(1, "\n", 1);
    exit(1);
}
