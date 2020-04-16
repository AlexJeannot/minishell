#include "../includes/exec.h"


void display_exec(char *exec)
{
    write(1, exec, ft_strlen(exec));
    write(1, ": ", 2);
}

void ft_error(char symbol, char *cmd, char *msg)
{
    write(1, "Minishell: ", 11);
    if (symbol != '\0')
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

void ft_exit(int status)
{
    free_lst();
    free_str_array(filtered_env);
    free_str_array(global_env);
    free_str(&piped_str);
    //system("leaks minishell");
    exit(status);
}



