/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 12:29:59 by ajeannot          #+#    #+#             */
/*   Updated: 2020/06/16 17:28:55 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	ft_program(char *cmd, char **args)
{
	if (cmd[0] == '.' || cmd[0] == '/')
	{
		if (execve(cmd, args, g_global_env) == -1)
			ft_error('\0', cmd, NULL, 127);
	}
	else
		ft_builtins(cmd, args);
}
