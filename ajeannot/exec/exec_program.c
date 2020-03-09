/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 12:29:59 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/09 13:37:09 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_program(char *args)
{
    char **tab_args;

    tab_args = ft_split(args, ' ');
    execve(tab_args[0], tab_args, global_env);
}
