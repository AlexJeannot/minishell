/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:00:33 by ajeannot          #+#    #+#             */
/*   Updated: 2020/06/17 14:41:12 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	update_oldpwd(int pwd_index, int oldpwd_index)
{
	char *old_pwd;
	char *add_pwd;

	if (pwd_index == -1 && pwd_check == 1)
		add_pwd = ft_strdup("");
	else
		add_pwd = ft_strdup(pwd_path);
	if (!(old_pwd = (char *)malloc(sizeof(char) * (ft_strlen(add_pwd) + 8))))
		ft_error('\0', "Malloc", NULL, 1);
	ft_strcpy(old_pwd, "OLDPWD=");
	ft_strcat(old_pwd, add_pwd);
	free_str(&global_env[oldpwd_index]);
	global_env[oldpwd_index] = old_pwd;
	free_str(&add_pwd);
}

void	update_pwd(int pwd_index, char *new_path)
{
	char *new_pwd;

	if (!(new_pwd = (char *)malloc(sizeof(char) * (ft_strlen(new_path) + 5))))
		ft_error('\0', "Malloc", NULL, 1);
	ft_strcpy(new_pwd, "PWD=");
	ft_strcat(new_pwd, new_path);
	if (pwd_index >= 0)
	{
		free_str(&global_env[pwd_index]);
		global_env[pwd_index] = new_pwd;
	}
	else
		global_env = extend_array_str(global_env
		, new_pwd, str_array_length(global_env));
}

void	update_env(char *new_path)
{
	int pwd_index;
	int oldpwd_index;

	pwd_index = search_in_array(global_env, "PWD", '=');
	oldpwd_index = search_in_array(global_env, "OLDPWD", '=');
	if (oldpwd_index != -1)
		update_oldpwd(pwd_index, oldpwd_index);
	if (pwd_index != -1)
		update_pwd(pwd_index, new_path);
	free_str(&pwd_path);
	pwd_path = ft_strdup(new_path);
	free_str(&new_path);
}

void	ft_cd(char **args)
{
	char	*path;
	int		result_chdir;

	path = select_path(args[0]);
	if (path[ft_strlen(path) - 1] == '/' && ft_strlen(path) > 1)
		path[ft_strlen(path) - 1] = '\0';
	result_chdir = chdir(path);
	if (result_chdir == -1)
	{
		free_str(&path);
		ft_error('\0', "cd", NULL, 1);
	}
	else
		update_env(path);
}
