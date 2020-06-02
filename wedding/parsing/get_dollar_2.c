/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dollar_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 12:41:27 by cbouleng          #+#    #+#             */
/*   Updated: 2020/06/02 12:41:37 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char	*get_startline(char *str, int j)
{
	char	*start;
	int		y;

	if (!(start = malloc(j)))
		ft_error('\0', "Malloc", NULL);
	y = 0;
	while (y < j)
	{
		start[y] = str[y];
		y++;
	}
	start[y] = '\0';
	return (start);
}

char	*get_endline(char *str, int j)
{
	char	*end;
	int		len;
	int		k;

	len = 0;
	j++;
	while ((str[j] >= '0' && str[j] <= '9') ||
			(str[j] >= 'a' && str[j] <= 'z') ||
			(str[j] >= 'A' && str[j] <= 'Z'))
		j++;
	k = j;
	while (str[j++])
		len++;
	if (!(end = malloc(len + 1)))
		ft_error('\0', "Malloc", NULL);
	len = 0;
	while (str[k])
		end[len++] = str[k++];
	end[len] = '\0';
	return (end);
}

char	*get_env_name_2check(char *str, int j)
{
	int		len;
	int		i;
	char	*tmp;

	j++;
	len = j;
	i = 0;
	while (str[j] && str[j] != ' ')
		j++;
	if (!(tmp = malloc(j - len + 1)))
		ft_error('\0', "Malloc", NULL);
	while (len < j && ((str[len] >= '0' && str[len] <= '9') ||
				(str[len] >= 'a' && str[len] <= 'z') || (str[len] >= 'A' &&
					str[len] <= 'Z')))
		tmp[i++] = str[len++];
	tmp[i] = '\0';
	return (tmp);
}

t_value	new_value(char *str, int j)
{
	t_value	v;
	int		len;
	int		i;

	v.name = get_env_name_2check(str, j);
	i = 0;
	while (global_env[i] && !ft_envcmp(global_env[i], v.name))
		i++;
	j = 0;
	while (global_env[i][j] != '=')
		j++;
	len = 0;
	v.i = i;
	v.j = j + 1;
	while (global_env[i][++j])
		len++;
	if (!(v.value = malloc(len + 1)))
		ft_error('\0', "Malloc", NULL);
	free_str(&v.name);
	return (v);
}

char	*get_env_value_2(char *str, int j)
{
	t_value v;

	v = new_value(str, j);
	v.y = 0;
	while (global_env[v.i][v.j])
		v.value[v.y++] = global_env[v.i][v.j++];
	v.value[v.y] = '\0';
	return (v.value);
}
