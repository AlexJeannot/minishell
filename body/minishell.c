/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:21:45 by ajeannot          #+#    #+#             */
/*   Updated: 2020/06/16 16:53:49 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	main(int argc, char **argv, char **env)
{
	int		ret_gnl;
	int		exit_status;
	char	*line;

	(void)argc;
	(void)argv;
	setup_env(argv, env, &exit_status);
	while (1)
	{
	//	exec_prompt();
		ret_gnl = get_next_line(0, &line);
		if (line && line[0])
			exit_status = exec_command_line(line, exit_status);
		else if (ret_gnl == 0)
			quit_shell_eof(line, exit_status);
		free_command_line(line);
	}
}
