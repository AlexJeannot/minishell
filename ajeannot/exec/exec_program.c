/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:47:48 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/06 18:59:38 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_path(char *cmd, char **env)
{
    int i;
    char *path;
    char **tab_path;
    char **tab_arg;
    char **final_tab;

    tab_arg = ft_split(cmd, ' ');
    i = 0;
    while (env[i] && (strcmp("PATH", ft_split(env[i], '=')[0])) != 0)
        i++;
    tab_path = ft_split(ft_split(env[i], '=')[1], ':');
    i = 0;
    while (tab_path[i])
    {
        i++;
    }
    final_tab = (char **)malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (tab_path[i])
    {
        path = (char *)malloc(sizeof(char) * (ft_strlen(tab_arg[0]) + ft_strlen(tab_path[i]) + 2));
        path = strcat(path, tab_path[i]);
        path[ft_strlen(tab_path[i])] = '/';
        path = strcat(path, tab_arg[0]);
        final_tab[i] = path;
        i++;
    }
    final_tab[i] = NULL;

    i = 0;
    while (final_tab[i])
    {
        execve(final_tab[i], tab_arg, env);
        i++;
    }
}
