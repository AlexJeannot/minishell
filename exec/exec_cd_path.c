/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 17:17:11 by ajeannot          #+#    #+#             */
/*   Updated: 2020/06/16 17:19:22 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

char	*previous_dir(char *input_path)
{
	char	*path;
	char	*complex_path;
	int		path_len;

	path = ft_strdup(g_pwd_path);
	path_len = ft_strlen(path);
	complex_path = NULL;
	while (path_len > 1 && path[path_len] != '/')
		path_len--;
	path[path_len] = '\0';
	if (input_path[2])
	{
		if (!(complex_path = (char *)malloc(sizeof(char) * (ft_strlen(path)
		+ ft_strlen(input_path) - 1))))
			ft_error('\0', "Malloc", NULL, 1);
		ft_strcpy(complex_path, path);
		ft_strcat(complex_path, &input_path[2]);
		free_str(&path);
		path = complex_path;
	}
	return (path);
}

char	*relative_path(char *input_path)
{
	char *actual_path;
	char *final_path;

	actual_path = ft_strdup(g_pwd_path);
	if (!(final_path = (char *)malloc(sizeof(char)
	* (ft_strlen(actual_path) + ft_strlen(input_path) + 2))))
		ft_error('\0', "Malloc", NULL, 1);
	ft_strcpy(final_path, actual_path);
	if (ft_strlen(actual_path) > 1)
		ft_strcat(final_path, "/");
	ft_strcat(final_path, input_path);
	free_str(&actual_path);
	return (final_path);
}

char	*absolute_path(char *input_path)
{
	char *actual_path;
	char *final_path;

	actual_path = get_env_value("HOME");
	if (!(final_path = (char *)malloc(sizeof(char)
	* (ft_strlen(actual_path) + ft_strlen(input_path)))))
		ft_error('\0', "Malloc", NULL, 1);
	ft_strcpy(final_path, actual_path);
	ft_strcat(final_path, "/");
	ft_strcat(final_path, &input_path[2]);
	free_str(&actual_path);
	return (final_path);
}

char	*select_path(char *input_path)
{
	char *output_path;

	if (input_path == NULL)
		output_path = get_env_value("HOME");
	else if ((input_path[0] == '.' && !(input_path[1]))
			|| (input_path[0] == '.' && input_path[1] == '/'))
		output_path = ft_strdup(g_pwd_path);
	else if (input_path[0] == '.' && input_path[1] == '.'
			&& (input_path[2] == '/' || !(input_path[2])))
		output_path = previous_dir(input_path);
	else if (input_path[0] == '~' && input_path[1] == '/')
		output_path = absolute_path(input_path);
	else if (input_path[0] == '/')
		output_path = ft_strdup(input_path);
	else
		output_path = relative_path(input_path);
	return (output_path);
}
