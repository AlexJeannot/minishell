/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 15:09:54 by cbouleng          #+#    #+#             */
/*   Updated: 2020/06/17 17:32:08 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char	*g_map;

void	check_simple_quote(char *str)
{
	int i;

	i = 0;
	while (g_map[i])
	{
		if (g_map[i] == '3')
		{
			i++;
			while (g_map[i] == '1')
				i++;
			if (g_map[i] != '3' || str[i] != '\'')
				ft_error('\0', NULL, "Error : multi-line opened by <\'>\n", 1);
		}
		i++;
	}
}

void	check_double_quote(char *str)
{
	int	i;

	i = 0;
	while (g_map[i])
	{
		if (g_map[i] == '4')
		{
			i++;
			while (g_map[i] == '2')
				i++;
			if (g_map[i] != '4' || str[i] != '"')
				ft_error('\0', NULL, "Error : multi-line opened by <\">\n", 1);
		}
		i++;
	}
}

void	check_bs(char *str)
{
	int	i;

	i = ft_strlen(str);
	i--;
	while (i >= 0)
	{
		if (str[i] == '\\' && (!str[i + 1])//|| str[i + 1] == ' ')
			&& g_map[i] == '0')
		{
			if (!is_esc(str, i))
				ft_error('\0', NULL, "Error : multi-line opened by <\\>\n", 1);
			else
				return ;
		}
		i--;
	}
}

void	check(char *line)
{
	g_map = map_quote(line, 0);
	check_simple_quote(line);
	check_double_quote(line);
	check_bs(line);
	check_rdc(line, g_map);
	check_rdo(line, g_map);
	free_str(&g_map);
}
