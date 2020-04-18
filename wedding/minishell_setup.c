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

void setup_env(char **env)
{
    errno = 0;
    child_pid = -1;
    global_env = duplicate_array(env, NULL, '\0');
    filtered_env = filter_env(global_env, NULL);
    signal(SIGINT, signal_manager);
    signal(SIGQUIT, signal_manager);
}

void setup_shell(int *exit_status, int process_fd[2])
{
    *exit_status = 0;
    pipe(process_fd);
}

void setup_command(int exit_status, int process_fd[2], int redirection_fd[2])
{
    replace_exit_status(exit_status);
    get_dollar();
    clear_before_exec();
    if (lst->pipe == 1)
	    pipe(process_fd);
   	pipe(redirection_fd);
}