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


int main(int argc, char **argv, char **env)
{
    char *line;
    int ret_gnl;
    int process_fd[2];
    int redirection_fd[2];
    int exit_status;

    (void)argc;
    (void)argv;
    setup_env(env);
    while (1)
    {
     	exec_prompt();
        setup_shell(&exit_status, process_fd);
        ret_gnl = get_next_line(0, &line);
        if (line && line[0])
            exit_status = exec_command_line(exit_status, process_fd, redirection_fd, line);
        else if (ret_gnl == 0)
            quit_shell_eof(line);
        free_command_line(line, process_fd, redirection_fd);
    }
}
