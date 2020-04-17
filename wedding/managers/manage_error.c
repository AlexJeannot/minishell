#include "../includes/exec.h"


void display_exec(char *exec)
{
    write(1, exec, ft_strlen(exec));
    write(1, ": ", 2);
}

void ft_error(char symbol, char *cmd, char *msg)
{
    write(1, "Minishell: ", 11);
    if (cmd && !ft_strcmp(cmd, "rd"))
        ft_error_rd(msg, symbol);
    else
    {
        if (cmd)
            display_exec(cmd);
        if (msg)
            write(1, msg, ft_strlen(msg));
        else
            write(1, strerror(errno), ft_strlen(strerror(errno)));
    }
    write(1, "\n", 1);
    ft_exit(1);
}