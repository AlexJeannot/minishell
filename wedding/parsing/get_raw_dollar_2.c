/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_raw_dollar_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 16:37:10 by cbouleng          #+#    #+#             */
/*   Updated: 2020/05/25 16:39:42 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char				*raw_get_startline(int i, int j)
{
	char	*start;
	int		y;

	if (!(start = malloc(j)))
		ft_error('\0', "Malloc", NULL);
	y = 0;
	while (y < j)
	{
		start[y] = lst->raw[i][y];
		y++;
	}
	start[y] = '\0';
	return (start);
}

char				*raw_get_endline(int i, int j)
{
	char	*end;
	int		len;
	int		k;

	len = 0;
	j++;
	while ((lst->raw[i][j] >= '0' && lst->raw[i][j] <= '9') ||
		(lst->raw[i][j] >= 'a' && lst->raw[i][j] <= 'z') ||
		(lst->raw[i][j] >= 'A' && lst->raw[i][j] <= 'Z'))
		j++;
	k = j;
	while (lst->raw[i][j++])
		len++;
	if (!(end = malloc(len + 1)))
		ft_error('\0', "Malloc", NULL);
	len = 0;
	while (lst->raw[i][k])
		end[len++] = lst->raw[i][k++];
	end[len] = '\0';
	return (end);
}

static t_value		raw_new_value(int i, int j)
{
	t_value	v;
	int		len;

	v.name = get_env_name_2check(lst->raw[i], j);
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

char				*get_env_value_3(int i, int j)
{
	t_value v;

	v = raw_new_value(i, j);
	v.y = 0;
	while (global_env[v.i][v.j])
		v.value[v.y++] = global_env[v.i][v.j++];
	v.value[v.y] = '\0';
	return (v.value);
}

t_dolls				raw_dolls_value(int i, int j)
{
	t_dolls dls;

	dls.value = get_env_value_3(i, j);
	dls.startline = raw_get_startline(i, j);
	dls.endline = raw_get_endline(i, j);
	dls.len = ft_strlen(dls.value) + ft_strlen(dls.startline)
	+ ft_strlen(dls.endline);
	return (dls);
}
