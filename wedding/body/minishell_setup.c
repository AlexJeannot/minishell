#include "../includes/exec.h"

void signal_manager(int sig)
{
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

int setup_pipe_and_process(int exit_status)
{
    int prev_pipe;
    int prev_fd;
    int p_fd[2];

    prev_fd = -1;
    prev_pipe = -1;
    lst_free = lst;
	while (lst)
	{
        if (prev_pipe == 0)
            wait_for_child(exit_status, p_fd[0]);
		if (lst->cmd && ft_strcmp(lst->cmd, "exit") == 0 && lst->pipe != 1 && prev_pipe != 1)
            ft_exit(0);
        if ((pipe(p_fd)) == -1)
            ft_error('\0', "Pipe", NULL);
        if ((child_pid = fork()) == -1)
            ft_error('\0', "Fork", NULL);
        if (child_pid > 0)
            setup_parent(&prev_fd, &prev_pipe, p_fd);
        else
        {
            setup_child(prev_fd, prev_pipe, p_fd);
            exec_child(prev_pipe, exit_status, p_fd[1]);
        }
	}
    return (p_fd[0]);
}
