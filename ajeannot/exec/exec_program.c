/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 12:29:59 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/09 18:26:14 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_program(char *args)
{
    char **tab_args;

    tab_args = ft_split(args, ' ');
    if (tab_args[0][0] == '.')
        execve(tab_args[0], tab_args, global_env);
    else
    {
        ft_builtins(args);
    }
    free_str_array(tab_args);
}
