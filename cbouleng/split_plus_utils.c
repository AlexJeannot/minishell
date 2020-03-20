/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_plus_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:51:26 by cbouleng          #+#    #+#             */
/*   Updated: 2020/03/11 15:52:46 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_escaped(char *str, int i)
{
	if (str[i - 1] == '\\')
		return (1);
	return (0);
}

int		is_paired(char *str, int i)
{
	if (str[i] == '"')
	{
		i++;
		while (str[i] != '"' && str[i])
			i++;
		if (str[i] == '"')
			return (1);
	}
	else
	{
		i++;
		while (str[i] != '\'' && str[i])
			i++;
		if (str[i] == '\'')
			return (1);
	}
	return (0);
}

static int		map_s_help(int i)
{
	if (map_s)
	{
		if (map_s[i] != '0')
			return (0);
	}
	return (1);
}

static int		map_d_help(int i)
{
	if (map_d)
	{
		if (map_d[i] != '0')
			return (0);
	}
	return (1);
}

char*	map_double_quote(char *str)
{
	char	*map_d;
	int 	i;

	i = ft_strlen(str);
	if (!(map_d = malloc(i + 1)))
		ft_exit(1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && !is_escaped(str, i) && is_paired(str, i)
			&& map_s_help(i))
		{
			map_d[i++] = '2';
			while (str[i] != '"' && !is_escaped(str, i))
				map_d[i++] = '2';
			map_d[i++] = '2';
		}
		else
			map_d[i++] = '0';
	}
	map_d[i] = '\0';
	return (map_d);
}

char	*map_simple_quote(char *str)
{
	char	*map_s;
	int 	i;

	i = ft_strlen(str);
	if (!(map_s = malloc(i + 1)))
		exit(1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !is_escaped(str, i) && is_paired(str, i)
			&& map_d_help(i))
		{
			map_s[i++] = '1';
			while (str[i] != '\'' && !is_escaped(str, i))
				map_s[i++] = '1';
			map_s[i++] = '1';
		}
		else
			map_s[i++] = '0';
	}
	map_s[i] = '\0';
	return (map_s);
}
