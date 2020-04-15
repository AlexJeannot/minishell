/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:21:45 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/09 19:45:50 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void setup_shell(char **env)
{
    errno = 0;
    global_env = duplicate_array(env, NULL, '\0');
    filtered_env = filter_env(global_env, NULL);
    signal(SIGINT, signal_manager);
    signal(SIGQUIT, signal_manager);
}

void setup_command(void)
{
    get_dollar();
    clear_before_exec();
    child_pid = fork();
}

void setup_end_command_line(char *line)
{
    free_str(line);
	free_lst();
    //free_str(piped_str);
    child_pid = -1;
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    char *line;
    int ret_gnl;
    int process_fd[2];
    int redirection_fd[2];
    int exit_status;

    setup_shell(env);
    while (1)
    {
     	display_prompt();
        pipe(process_fd);
        pipe(redirection_fd);
        ret_gnl = get_next_line(0, &line);
        exit_status = 0;
        if (line && line[0])
		{
            exit_status = exec_command_line(exit_status, process_fd, redirection_fd, line);
		}
        else if (ret_gnl == 0)
            ft_exit_2(NULL, 0);
        setup_end_command_line(line);
    }
}
