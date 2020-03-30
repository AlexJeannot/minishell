/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:00:33 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/09 18:22:25 by ajeannot         ###   ########.fr       */
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
    ft_strcpy(old_pwd, "OLDPWD=");
    ft_strcat(old_pwd, &global_env[pwd_index][4]);
    free_str(global_env[oldpwd_index]);
    global_env[oldpwd_index] = old_pwd;
    new_pwd = (char *)malloc(sizeof(char) * ft_strlen(new_path) + 5);
    ft_strcpy(new_pwd, "PWD=");
    ft_strcat(new_pwd, new_path);
    free_str(global_env[pwd_index]);
    global_env[pwd_index] = new_pwd;
    free_str(new_path);
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
    char *actual_path;
    char *final_path;

    actual_path = get_env_value("PWD");
    final_path = (char *)malloc(sizeof(char) * (ft_strlen(actual_path) + ft_strlen(input_path) + 2));
    ft_strcpy(final_path, actual_path);
    ft_strcat(final_path, "/");
    ft_strcat(final_path, input_path);
    return (final_path);
}

char *absolute_path(char *input_path)
{
    char *actual_path;
    char *final_path;

    actual_path = get_env_value("HOME");
    final_path = (char *)malloc(sizeof(char) * (ft_strlen(actual_path) + ft_strlen(input_path)));
    ft_strcpy(final_path, actual_path);
    ft_strcat(final_path, "/");
    ft_strcat(final_path, &input_path[2]);
    return (final_path);
}

char *select_path(char *input_path)
{
    char *output_path;

    if (input_path == NULL)
        output_path = get_env_value("HOME");
    else if (input_path[0] == '.' && !(input_path[1]))
        output_path = get_env_value("PWD");
    else if (ft_strcmp(input_path, "..") == 0)
        output_path = previous_dir();
    else if (input_path[0] == '~' && input_path[1] == '/')
        output_path = absolute_path(input_path);
    else if (input_path[0] == '/')
        output_path = ft_strdup(input_path);
    else
        output_path = relative_path(input_path);
    return (output_path);
}

void ft_cd(char **args)
{
    char *path;
    int result_chdir;

    path = select_path(args[0]);
    result_chdir = chdir(path);
    if (result_chdir == -1)
    {
        free(path);
        display_error("cd", NULL);
    }
    else
        update_env(path);
    free_str_array(args);
}
