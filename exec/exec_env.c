/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 17:20:49 by ajeannot          #+#    #+#             */
/*   Updated: 2020/06/16 17:20:59 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	ft_error_env(char *file)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	ft_exit(127);
}

void	ft_env(char **args)
{
	if (args[0])
		ft_error_env(args[0]);
	display_str_array(filtered_env);
}
