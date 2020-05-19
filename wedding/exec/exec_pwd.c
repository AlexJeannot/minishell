#include "../includes/exec.h"

void ft_pwd(void)
{
    char *path;

    path = get_env_value("PWD");
    ft_putstr_fd(path, 1);
    write(1, "\n", 1);
}