/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:47:48 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/09 12:29:13 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_builtins(char *args)
{
    int count;
    int index_path;
    char *path;
    char **tab_path;
    char **tab_args;

    tab_args = ft_split(args, ' ');
    count = 0;
    index_path = search_in_array(global_env, "PATH", '=');
    tab_path = ft_split(ft_split(global_env[index_path], '=')[1], ':');
    while (tab_path[count])
    {
        path = (char *)malloc(sizeof(char) * (ft_strlen(tab_args[0]) + ft_strlen(tab_path[count]) + 2));
        path = ft_strcat(path, tab_path[count]);
        path[ft_strlen(tab_path[count])] = '/';
        path = ft_strcat(path, tab_args[0]);
        tab_path[count] = path;
        count++;
    }
    tab_path[count] = NULL;

    count = 0;
    while (tab_path[count])
    {
        execve(tab_path[count], tab_args, global_env);
        count++;
    }
}
