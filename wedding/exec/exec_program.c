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

#include "../includes/exec.h"

void ft_program(t_list *lst, char *cmd, char **args)
{
    if (cmd[0] == '.' || cmd[0] == '/')
    {
        if (execve(cmd, args, global_env) == -1)
            display_error(cmd, NULL);
    }
    else
        ft_builtins(lst, cmd, args);
}
