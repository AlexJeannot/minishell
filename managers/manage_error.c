/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 17:40:16 by ajeannot          #+#    #+#             */
/*   Updated: 2020/06/16 17:40:52 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	display_exec(char *exec)
{
	write(1, exec, ft_strlen(exec));
	write(1, ": ", 2);
}

void	ft_error(char symbol, char *cmd, char *msg, int status)
{
	write(1, "Minishell: ", 11);
	if (cmd && !ft_strcmp(cmd, "rd"))
		ft_error_rd(msg, symbol);
	else
	{
		if (cmd)
			display_exec(cmd);
		if (msg)
			write(1, msg, ft_strlen(msg));
		else
			write(1, strerror(g_erno), ft_strlen(strerror(g_erno)));
	}
	write(1, "\n", 1);
	free_lst();
	free_str_array(g_filtered_env);
	free_str_array(g_global_env);
	exit(status);
}
