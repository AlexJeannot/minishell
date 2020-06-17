/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 17:21:05 by cbouleng          #+#    #+#             */
/*   Updated: 2020/06/11 18:24:30 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char		*g_map;

int			esc_case(char *str, int i)
{	
	if (!is_esc(str, i - 1) && str[i - 1] == '\\' && g_map[i - 1] == '0')
		return (0);
	return (1);
}

static void	mapping(char *str)
{
	int	flag_d;
	int	flag_s;
	int	i;

	flag_d = 1;
	flag_s = 1;
	i = 0;
	while (str[i])
	{
		if (flag_d > 0 || flag_s > 0)
			g_map[i] = '0';
		if (flag_d < 0)
			g_map[i] = '2';
		if (flag_s < 0)
			g_map[i] = '1';
		if (str[i] == '"' && !is_esc(str, i) && flag_s > 0 && (flag_d *= -1))
			g_map[i] = '4';
		if (str[i] == '\'' && flag_d > 0 && esc_case(str, i) && (flag_s *= -1))
			g_map[i] = '3';
		i++;
	}
	g_map[i] = '\0';
}

//static void	mapping_2(char *str, int flag_d, int flag_s, int i)
//{
//	while (str[i])
//	{
//		if (flag_d > 0 || flag_s > 0)
//			g_map[i] = '0';
//		if (flag_d < 0)
//			g_map[i] = '2';
//		if (flag_s < 0)
//			g_map[i] = '1';
//		if (str[i] == '"' && str[i - 1] != '\\' && flag_s > 0 && (flag_d *= -1))
//			g_map[i] = '4';
//		if (str[i] == '\'' && esc_case(str, i) && flag_d > 0 && (flag_s *= -1))
//			g_map[i] = '3';
//		if (str[i] == '\'' && str[i - 1] == '\\' && g_map[i - 1] == '0')
//			g_map[i] = '0';
//		i++;
//	}
//	g_map[i] = '\0';
//}

char		*map_quote(char *str, int pos)
{
	if (!(g_map = malloc(ft_strlen(str) + 1)))
		ft_error('\0', "Malloc", NULL);
	if (pos)
		mapping(str);
		//mapping_2(str, 1, 1, i);
	else
		mapping(str);
	return (g_map);
}
