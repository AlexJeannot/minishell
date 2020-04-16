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

#include "../includes/exec.h"

void update_env(char *new_path)
{
    int pwd_index;
    int oldpwd_index;
    char *new_pwd;
    char *old_pwd;

    pwd_index = search_in_array(global_env, "PWD", '=');
    oldpwd_index = search_in_array(global_env, "OLDPWD", '=');
    if (!(old_pwd = (char *)malloc(sizeof(char) * (ft_strlen(global_env[pwd_index]) + 4))))
        ft_error('\0', "Malloc", NULL);
    ft_strcpy(old_pwd, "OLDPWD=");
    ft_strcat(old_pwd, &global_env[pwd_index][4]);
    free_str(&global_env[oldpwd_index]);
    global_env[oldpwd_index] = old_pwd;
    if (!(new_pwd = (char *)malloc(sizeof(char) * (ft_strlen(new_path) + 5))))
    	ft_error('\0', "Malloc", NULL);
    ft_strcpy(new_pwd, "PWD=");
    ft_strcat(new_pwd, new_path);
    free_str(&global_env[pwd_index]);
    global_env[pwd_index] = new_pwd;
    free_str(&new_path);
}

void ft_cd(char **args)
{
    char *path;
    int result_chdir;

    path = select_path(args[0]);
    result_chdir = chdir(path);
    if (result_chdir == -1)
    {
        free_str(&path);
        ft_error('\0', "cd", NULL);
    }
    else
        update_env(path);
}
