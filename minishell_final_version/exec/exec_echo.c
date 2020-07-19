/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 17:19:45 by ajeannot          #+#    #+#             */
/*   Updated: 2020/06/16 17:20:25 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	ft_echo(char **args)
{
	int count;
	int option;

	count = 0;
	option = 0;
	if (args[count] && ft_strcmp(args[count], "-n") == 0)
	{
		while (ft_strcmp(args[count], "-n") == 0)
			count++;
		option = 1;
	}
	while (args[count])
	{
		ft_putstr_fd(args[count], 1);
		if (args[count + 1])
			write(1, " ", 1);
		count++;
	}
	if (!args[0] || !(option))
		write(1, "\n", 1);
}
