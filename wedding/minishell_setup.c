#include "./includes/exec.h"

void signal_manager(int sig)
{
    printf("sig = %d\n", sig);
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        if (child_pid == -1)
            exec_prompt();
    }
    if (sig == SIGQUIT)
    {
        if (child_pid && child_pid > 0)
        {
            write(1, "Quit: 3\n", 8);
            kill(child_pid, SIGKILL);
        }
    }
}

void setup_env(char **env, int *exit_status)
{
    errno = 0;
    child_pid = -1;
    global_env = duplicate_array(env, NULL, '\0');
    filtered_env = filter_env(global_env, NULL);
    *exit_status = 0;
    signal(SIGINT, signal_manager);
    signal(SIGQUIT, signal_manager);
}

void setup_command(int exit_status)
{
    replace_exit_status(exit_status);
    get_dollar();
    clear_before_exec();
}

void close_fd(int fd)
{
    if (fd >= 0)
    {
        close(fd);
        fd = -1;
    }
}

void setup_pipe_and_process(int exit_status)
{
    int prev_pipe;
    int prev_fd;
    int ret_pchild;

    prev_fd = -1;
    prev_pipe = -1;
    ret_pchild = 0;
	while (lst)
	{
        pipe(p_fd);
        /* INCLURE ERROR PIPE ICI*/
        if (prev_pipe == 0)
        {
            waitpid(child_pid, &ret_pchild, 0);
            if (WIFEXITED(ret_pchild))
                exit_status = WEXITSTATUS(ret_pchild);
        }
        child_pid = fork();
        /* INCLURE ERROR FORK ICI*/

        if (child_pid > 0)
        {
            close_fd(prev_fd);
            prev_fd = p_fd[0];
            prev_pipe = lst->pipe;
		    lst = lst->next;
        }
        else
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
            exec_child(prev_pipe, exit_status);
        }
	}
}