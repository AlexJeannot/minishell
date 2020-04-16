#include "../includes/exec.h"

int receive_pipe(int process_fd[2])
{
    free_str(&piped_str);
    piped_str = read_from_fd(process_fd);
    return (0);
}