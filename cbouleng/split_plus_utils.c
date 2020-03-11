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

char	*map_double_quote(char *str)
{
	char	*map_d;
	int 	i;

	i = ft_strlen(str);
	if (!(map_d = malloc(i + 1)))
		exit(1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && !is_escaped(str, i))
		{
			map_d[i++] = '1';
			while (str[i] != '"' && !is_escaped(str, i))
				map_d[i++] = '1';
			map_d[i++] = '1';
		}
		map_d[i] = '0';
		i++;
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
		if (str[i] == '\'' && !is_escaped(str, i))
		{
			map_s[i++] = '2';
			while (str[i] != '\'' && !is_escaped(str, i))
				map_s[i++] = '2';
			map_s[i++] = '2';
		}
		map_s[i] = '0';
		i++;
	}
	map_s[i] = '\0';
	return (map_s);
}
