#include "../includes/exec.h"

void close_fd(int fd)
{
    if (fd >= 0)
    {
        close(fd);
        fd = -1;
    }
}

void setup_parent(int *prev_fd, int *prev_pipe, int p_fd[2])
{
    close(p_fd[1]);
    if (*prev_fd >= 0)
        close(*prev_fd);
    *prev_fd = p_fd[0];
    *prev_pipe = lst->pipe;
    lst = lst->next;
}

void setup_child(int prev_fd, int prev_pipe, int p_fd[2])
{
    close(p_fd[0]);
    if (prev_fd >= 0)
    {
        if (prev_pipe == 1)
            dup2(prev_fd, STDIN_FILENO);
        close(prev_fd);
    }
    if (lst->pipe == 1 && lst->rdc_type == 0)
    {
        dup2(p_fd[1], STDOUT_FILENO);
        close(p_fd[1]);
    }
}

int wait_for_child(int exit_status, int read_end)
{
    int ret_pchild;
    
    waitpid(child_pid, &ret_pchild, 0);
    if (WIFEXITED(ret_pchild))
        exit_status = WEXITSTATUS(ret_pchild);
    receive_env(read_end);
    filtered_env = filter_env(global_env, filtered_env);
    return (exit_status);
}