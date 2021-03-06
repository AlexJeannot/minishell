/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_stock_rd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 14:14:14 by cbouleng          #+#    #+#             */
/*   Updated: 2020/05/27 14:15:52 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char	*g_map;

int		is_rd(char *str, int i)
{
	if (!is_esc(str, i) && g_map[i] == '0')
	{
		if (str[i] == '>' && str[i + 1] == '>')
			return (1);
		if (str[i] == '>' && str[i - 1] != '>')
			return (1);
		if (str[i] == '<')
			return (1);
	}
	return (0);
}

char	*clear_stock_rd(char *str)
{
	int	i;

	i = 0;
	g_map = map_quote(str);
	while (str[i])
	{
		if (is_rd(str, i))
		{
			str[i++] = ' ';
			while (str[i] == ' ')
				i++;
			while (is_name(str, i))
				str[i++] = ' ';
		}
		if (!is_rd(str, i))
			i++;
	}
	free_str(&g_map);
	return (str);
}
