#include "../includes/exec.h"

void ft_exit(int status)
{
    free_lst();
    free_str_array(filtered_env);
    free_str_array(global_env);
    free_str(&piped_str); 
	//ft_leaks("AT EXIT");
    exit(status);
}