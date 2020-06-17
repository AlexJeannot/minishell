/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:46:22 by ajeannot          #+#    #+#             */
/*   Updated: 2020/06/16 17:40:00 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

char	*read_from_fd(int read_end)
{
	int ret;
	char buf[101];
	char *output_str;

	output_str = NULL;
	while ((ret = read(read_end, buf, 100)) > 0)
	{
		buf[ret] = '\0';
		output_str = ft_join(output_str, buf
		, ft_len(output_str), ft_len(buf));
		if (ret < 100)
			break ;
	}
	return (output_str);
}

char	*get_env_value(char *var)
{
	int count;
	char *env_value;
	char **split_result;

	count = 0;
	while (global_env[count])
	{
		split_result = ft_split(global_env[count], '=');
		if (strcmp(split_result[0], var) == 0)
		{
			env_value = ft_strdup(split_result[1]);
			free_str_array(split_result);
			return (env_value);
		}
		free_str_array(split_result);
		count++;
	}
	return (NULL);
}

void	send_env(int write_pend, int write_pwdend)
{
	int count;

	count = 0;
	while (global_env[count])
	{
		write(write_pend, global_env[count]
		, ft_strlen(global_env[count]));
		write(write_pend, "\n", 1);
		count++;
	}
	write(write_pwdend, pwd_path, ft_strlen(pwd_path));
	close(write_pend);
	close(write_pwdend);
}

void	receive_env(int read_pend, int read_pwdend)
{
	char *str_env;
	char *new_path;
	char **tab_env;

	str_env = read_from_fd(read_pend);
	if (str_env)
	{
		tab_env = ft_split(str_env, '\n');
		global_env = duplicate_array(tab_env, global_env, '\0');
		free_str(&str_env);
		free_str_array(tab_env);
	}
	new_path = read_from_fd(read_pwdend);
	if (new_path)
	{
		if (ft_strcmp(new_path, pwd_path) != 0)
			pwd_check = 0;
		free_str(&pwd_path);
		pwd_path = ft_strdup(new_path);
		free_str(&new_path);
		chdir(pwd_path);
	}
	close(read_pwdend);
}
