#include "../includes/exec.h"

void ft_exit(int status)
{
	if (lst && ft_strcmp(lst->cmd, "exit") == 0
        && child_pid != 0)
        write(1, "exit\n", 5);
    free_lst();
    free_str_array(filtered_env);
    free_str_array(global_env);
	//ft_leaks("AT EXIT");
    exit(status);
}