/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 17:50:53 by ajeannot          #+#    #+#             */
/*   Updated: 2020/06/16 17:51:09 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	close_fd(int fd)
{
	if (fd >= 0)
	{
		close(fd);
		fd = -1;
	}
}

void	setup_parent(int *prev_fd, int *prev_pipe, int p_fd[2], int pwd_fd[2])
{
	int count;

	count = 0;
	close(p_fd[1]);
	close(pwd_fd[1]);
	if (*prev_fd >= 0)
		close(*prev_fd);
	*prev_fd = p_fd[0];
	*prev_pipe = lst->pipe;
	if (lst->cmd && ft_strcmp(lst->cmd, "unset") == 0)
	{
		while (lst->arg[count])
		{
			if (ft_strcmp(lst->arg[count], "PWD") == 0)
				pwd_check = 1;
			count++;
		}
	}
	lst = lst->next;
}

void	setup_child(int prev_fd, int prev_pipe, int p_fd[2], int pwd_fd[2])
{
	close(p_fd[0]);
	close(pwd_fd[0]);
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

int	wait_for_child(int exit_status, int read_pend, int read_pwdend)
{
	int ret_pchild;

	waitpid(child_pid, &ret_pchild, 0);
	if (WIFEXITED(ret_pchild))
		exit_status = WEXITSTATUS(ret_pchild);
	receive_env(read_pend, read_pwdend);
	filtered_env = filter_env(global_env, filtered_env);
	return (exit_status);
}
