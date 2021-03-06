/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 15:12:32 by cbouleng          #+#    #+#             */
/*   Updated: 2020/06/20 13:07:52 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	check_rdc_case(char *str, int i)
{
	int	j;

	if (str[i] == '>' && str[i - 1] != '>' && str[i + 1] != '>')
	{
		j = i + 1;
		while (str[j] == ' ')
			j++;
		if (!is_name(str, j))
			ft_error(str[j], "rd",
			"syntax error near unexpected symbol `", 258);
	}
	if (str[i] == '>' && str[i + 1] == '>' && str[i - 1] != '>')
	{
		j = i + 2;
		while (str[j] == ' ')
			j++;
		if (!is_name(str, j))
			ft_error(str[j], "rd",
			"syntax error near unexpected symbol `", 258);
	}
}

void	check_rdc(char *str, char *map)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (map[i] == '0' && !is_esc(str, i))
		{
			if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
				ft_error('>', "rd", "syntax error near symbol `", 258);
			check_rdc_case(str, i);
		}
		i++;
	}
}

void	check_rdo(char *str, char *map)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (map[i] == '0' && !is_esc(str, i))
		{
			if (str[i] == '<' && str[i + 1] == '<')
				ft_error('<', "rd", "syntax error near symbol `", 258);
			if (str[i] == '<')
			{
				j = i + 1;
				while (str[j] == ' ')
					j++;
				if (!is_name(str, j))
					ft_error(str[j], "rd", "syntax error near symbol `", 258);
			}
		}
		i++;
	}
}
