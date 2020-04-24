#include "./includes/exec.h"

void quit_shell_eof(char *line)
{
    free_str(&line);
    write(1, "exit\n", 5);
    ft_exit(0);
}

void free_command_line(char *line)
{
    free_str(&line);
    free_lst();
    child_pid = -1;
}