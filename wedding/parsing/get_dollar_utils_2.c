/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dollar_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 16:35:33 by cbouleng          #+#    #+#             */
/*   Updated: 2020/05/25 16:35:52 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char	*get_env_value_2(int i, int j)
{
	t_value v;

	v = new_value(i, j);
	v.y = 0;
	while (global_env[v.i][v.j])
		v.value[v.y++] = global_env[v.i][v.j++];
	v.value[v.y] = '\0';
	return (v.value);
}

char	*get_startline(int i, int j)
{
	char	*start;
	int		y;

	if (!(start = malloc(j)))
		ft_error('\0', "Malloc", NULL);
	y = 0;
	while (y < j)
	{
		start[y] = lst->arg[i][y];
		y++;
	}
	start[y] = '\0';
	return (start);
}

char	*get_endline(int i, int j)
{
	char	*end;
	int		len;
	int		k;

	len = 0;
	j++;
	while ((lst->arg[i][j] >= '0' && lst->arg[i][j] <= '9') ||
	(lst->arg[i][j] >= 'a' && lst->arg[i][j] <= 'z') ||
	(lst->arg[i][j] >= 'A' && lst->arg[i][j] <= 'Z'))
		j++;
	k = j;
	while (lst->arg[i][j++])
		len++;
	if (!(end = malloc(len + 1)))
		ft_error('\0', "Malloc", NULL);
	len = 0;
	while (lst->arg[i][k])
		end[len++] = lst->arg[i][k++];
	end[len] = '\0';
	return (end);
}
