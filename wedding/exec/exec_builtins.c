/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:47:48 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/09 19:35:40 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_builtins(char *cmd, char **args)
{
    int count;
    int index_path;
    char *path;
    char **tab_path;
//    char **split_result;

    count = 0;
    //printf("Dans builtins\n");
    index_path = search_in_array(global_env, "PATH", '=');
    tab_path = ft_split(ft_split(global_env[index_path], '=')[1], ':');
    while (tab_path[count])
    {
        path = (char *)malloc(sizeof(char) * (ft_strlen(cmd) + ft_strlen(tab_path[count]) + 2));
        path = ft_strcat(path, tab_path[count]);
        path[ft_strlen(tab_path[count])] = '/';
        path = ft_strcat(path, cmd);
        tab_path[count] = path;
        //printf("tab_path[count] = %s\n", tab_path[count]);
        count++;
    }
    tab_path[count] = NULL;

    count = 0;
//    printf("\n\n=========== PRE BUILTINS =========== \n\n");
//    display_array(global_env);
//    printf("\n\n=========== PRE BUILTINS =========== \n\n");

    int ret;
    while (tab_path[count])
    {
        ret = execve(tab_path[count], args, global_env);
        //printf("ret = %d\n", ret);
        count++;
    }
}
