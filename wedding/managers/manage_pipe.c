#include "../includes/exec.h"

int set_pipe(t_list *lst, int process_fd[2])
{
    int status;

    dup2(process_fd[1], STDOUT_FILENO);
    status = exec_instructions(lst);
    return (status);
}

int receive_pipe(int process_fd[2])
{
    piped_str = read_from_fd(process_fd);
    return (0);
}