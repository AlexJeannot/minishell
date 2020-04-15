#include "../includes/exec.h"

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

/*
void ft_error(char symbol, char *cmd, char *msg)
{
    write(1, "Minishell: ", 11);
    if (symbol != '\0')
        ft_error_rd(msg, symbol)
    else
    {
        if (cmd)
            display_exec(exec);
        if (msg)
            write(1, error_str, ft_strlen(error_str));
        else
            write(1, strerror(errno), ft_strlen(strerror(errno)));
    }
    write(1, "\n", 1);
    ft_exit(1);
}

void ft_exit(int status)
{
    free_str_array(filtered_env);
    free_str_array(global_env);
//    system("leaks minishell");
    exit(status);
}
*/


