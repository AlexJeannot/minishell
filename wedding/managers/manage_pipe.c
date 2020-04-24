#include "../includes/exec.h"

void close_fd(int fd)
{
    if (fd >= 0)
    {
        close(fd);
        fd = -1;
    }
}

void setup_parent(int *prev_fd, int *prev_pipe, int p_fd_exit)
{
    close_fd(*prev_fd);
    *prev_fd = p_fd_exit;
    *prev_pipe = lst->pipe;
    lst = lst->next;
}

void setup_child(int prev_fd, int prev_pipe, int p_fd[2])
{
    if (prev_fd >= 0)
    {
        if (prev_pipe == 1)
            dup2(prev_fd, STDIN_FILENO);
        else
            dup2(prev_fd, p_fd[0]);
        close_fd(prev_fd);
    }
    if (p_fd[1] >= 0 && lst->pipe == 1 && lst->rdc_type == 0)
    {
        dup2(p_fd[1], STDOUT_FILENO);
        close_fd(p_fd[1]);
    }
}

int wait_for_child(int exit_status)
{
    int ret_pchild;
    
    waitpid(child_pid, &ret_pchild, 0);
    if (WIFEXITED(ret_pchild))
        exit_status = WEXITSTATUS(ret_pchild);
    return (exit_status);
}