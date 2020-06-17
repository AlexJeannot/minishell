/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 17:00:39 by ajeannot          #+#    #+#             */
/*   Updated: 2020/06/16 17:07:43 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	signal_manager(int sig)
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

void	setup_command(int exit_status)
{
	replace_exit_status(exit_status);
	get_dollar();
	clear_before_exec();
}

void	setup_values(int *prev_fd, int *prev_pipe, int *r_pend, int *r_pwdend)
{
	*prev_fd = -1;
	*prev_pipe = -1;
	lst_free = lst;
	*r_pend = -1;
	*r_pwdend = -1;
}

int		check_child_and_exit(int status, int prev_pipe, int r_pend, int r_pwdend)
{
	if (prev_pipe == 0)
		status = wait_for_child(status, r_pend, r_pwdend);
	if (lst->cmd && ft_strcmp(lst->cmd, "exit") == 0
	&& lst->pipe != 1 && prev_pipe != 1)
		ft_exit(status);
	return (status);
}

int		*setup_pipe_and_process(int exit_status, int *read_fd)
{
	int	prev_pipe;
	int	prev_fd;
	int	p_fd[2];
	int	pwd_fd[2];

	setup_values(&prev_fd, &prev_pipe, &p_fd[0], &pwd_fd[0]);
	while (lst)
	{
		exit_status = check_child_and_exit(exit_status,
		prev_pipe, p_fd[0], pwd_fd[0]);
		if ((pipe(p_fd)) == -1 || (pipe(pwd_fd)) == -1)
			ft_error('\0', "Pipe", NULL, 1);
		if ((child_pid = fork()) == -1)
			ft_error('\0', "Fork", NULL, 1);
		if (child_pid > 0)
			setup_parent(&prev_fd, &prev_pipe, p_fd, pwd_fd);
		else
		{
			setup_child(prev_fd, prev_pipe, p_fd, pwd_fd);
			exec_child(prev_pipe, exit_status, p_fd[1], pwd_fd[1]);
		}
	}
	read_fd[0] = p_fd[0];
	read_fd[1] = pwd_fd[0];
	return (read_fd);
}