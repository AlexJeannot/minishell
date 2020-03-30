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

char **build_exec_array(char *exec, char **path_array)
{
    int count;
    char *exec_path;
    char **exec_array;

    count = 0;
    if (!(exec_array = (char **)malloc(sizeof(char *) * (array_length(path_array) + 1))))
        display_error(NULL, NULL);
    while (path_array[count])
    {
        if (!(exec_path = (char *)malloc(sizeof(char) * (ft_strlen(exec) + ft_strlen(path_array[count]) + 2))))
            display_error(NULL, NULL);
        ft_strcpy(exec_path, path_array[count]);
        ft_strcat(exec_path, "/");
        ft_strcat(exec_path, exec);
        exec_array[count] = exec_path;
        count++;
    }
    exec_array[count] = NULL;
    free_str_array(path_array);
    return (exec_array);
}

char **select_env(char *exec)
{
    if (ft_strcmp(exec, "env") == 0)
        return(filtered_env);
    else
        return(global_env);
}

void ft_builtins(char *exec, char **args)
{
    int count;
    int ret_exec;
    int index_path;
    char **path_array;
    char **exec_array;
    char **used_env;
    char **split_result;

    count = 0;
    index_path = search_in_array(global_env, "PATH", '=');
    split_result = ft_split(global_env[index_path], '=');
    path_array = ft_split(split_result[1], ':');
    exec_array = build_exec_array(exec, path_array);
    free_str_array(split_result);
    used_env = select_env(exec);
    while (exec_array[count])
    {
        ret_exec = execve(exec_array[count], args, used_env);
        count++;
    }
    if (ret_exec == -1)
        display_error(exec, "command not found");
}
