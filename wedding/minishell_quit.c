#include "./includes/exec.h"

void quit_shell_eof(char *line)
{
    free_str(&line);
    write(1, "exit\n", 5);
    ft_exit(0);
}

void free_command_line(char *line, int process_fd[2], int redirection_fd[2])
{
    close(process_fd[0]);
    close(process_fd[1]);
    close(redirection_fd[0]);
    close(redirection_fd[1]);
    free_str(&line);
    free_str(&piped_str);
    free_lst();
    child_pid = -1;
}