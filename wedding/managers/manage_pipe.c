#include "../includes/exec.h"

void stdout_redirection(int input_fd[2])
{
    dup2(input_fd[1], STDOUT_FILENO);
    close(input_fd[1]);
}

int receive_pipe(int process_fd[2])
{
    free_str(&piped_str);
    piped_str = read_from_fd(process_fd);
    return (0);
}