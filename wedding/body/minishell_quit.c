/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_quit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 16:59:56 by ajeannot          #+#    #+#             */
/*   Updated: 2020/06/16 17:00:22 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	quit_shell_eof(char *line, int exit_status)
{
	free_str(&line);
//	write(1, "exit\n", 5);
	ft_exit(exit_status);
}

void	free_command_line(char *line)
{
	free_str(&line);
	free_lst();
	child_pid = -1;
}
