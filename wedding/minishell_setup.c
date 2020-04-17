#include "./includes/exec.h"

void signal_manager(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        display_prompt();
    }
    if (sig == SIGQUIT)
    {
        if (child_pid > 0)
        {
            write(1, "\n", 1);
            ft_putnbr(child_pid);
            write(1, "      quit", 10);
            write(1, "\n", 1);
            kill(child_pid, SIGKILL);
        }
    }
}

void setup_env(char **env)
{
    errno = 0;
    global_env = duplicate_array(env, NULL, '\0');
    filtered_env = filter_env(global_env, NULL);
    signal(SIGINT, signal_manager);
    signal(SIGQUIT, signal_manager);
}

void setup_shell(int *exit_status, int process_fd[2], int redirection_fd[2])
{
    piped_str = NULL;
    *exit_status = 0;
    pipe(process_fd);
    pipe(redirection_fd);
}

void setup_command(int exit_status)
{
    replace_exit_status(exit_status);
    get_dollar();
    clear_before_exec();
}

void free_command_line(char *line)
{
    free_str(&line);
    free_str(&piped_str);
    free_lst();
    child_pid = -1;
}