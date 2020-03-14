/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:00:33 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/12 09:05:28 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void update_env(char *new_path)
{
    int pwd_index;
    int oldpwd_index;
    char *new_pwd;
    char *old_pwd;

    pwd_index = search_in_array(global_env, "PWD", '=');
    oldpwd_index = search_in_array(global_env, "OLDPWD", '=');
    old_pwd = (char *)malloc(sizeof(char) * ft_strlen(global_env[pwd_index]) + 4);
    old_pwd = ft_strncat(old_pwd, global_env[oldpwd_index], 7);
    old_pwd = ft_strcat(old_pwd, &global_env[pwd_index][4]);
    free(global_env[oldpwd_index]);
    global_env[oldpwd_index] = old_pwd;
    new_pwd = (char *)malloc(sizeof(char) * ft_strlen(new_path) + 5);
    new_pwd = ft_strncat(new_pwd, global_env[pwd_index], 4);
    new_pwd = ft_strcat(new_pwd, new_path);
    free(global_env[pwd_index]);
    global_env[pwd_index] = new_pwd;
    free(new_path);
}

char *previous_dir(void)
{
    char *path;
    int path_len;

    path = get_env_value("PWD");
    path_len = ft_strlen(path);
    while (path[path_len] != '/')
        path_len--;
    path[path_len] = '\0';
    return (path);
}

char *relative_path(char *input_path)
{
    char *path;
    char *pre_path;

    pre_path = get_env_value("PWD");
    path = (char *)malloc(sizeof(char) * (ft_strlen(pre_path) + ft_strlen(input_path) + 2));
    path = ft_strcat(path, pre_path);
    path = ft_strcat(path, "/");
    path = ft_strcat(path, input_path);
    return (path);
}

char *absolute_path(char *input_path)
{
    char *path;
    char *pre_path;

    pre_path = get_env_value("HOME");
    path = (char *)malloc(sizeof(char) * (ft_strlen(pre_path) + ft_strlen(input_path)));
    path = ft_strcat(path, pre_path);
    path = ft_strcat(path, "/");
    path = ft_strcat(path, &input_path[2]);
    return (path);
}

void ft_cd(char *args)
{
    char *path;
    char **tab_args;
    int result_chdir;
    //char **split_result;


    tab_args = ft_split(args, ' ');
    if (tab_args[1] == NULL)
        path = get_env_value("HOME");
    else if (strcmp(tab_args[1], "..") == 0)
        path = previous_dir();
    else if (tab_args[1][0] == '~' && tab_args[1][1] == '/')
        path = absolute_path(tab_args[1]);
    else if (tab_args[1][0] == '/')
        path = ft_strdup(tab_args[1]);
    else
        path = relative_path(tab_args[1]);

    result_chdir = chdir(path);
    if (result_chdir == -1)
    {
        printf("ERROR DIRECTORY\n");
        free(path);
    }
    else
        update_env(path);
    free_str_array(tab_args);
}
