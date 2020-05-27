/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_backslash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 14:01:58 by cbouleng          #+#    #+#             */
/*   Updated: 2020/05/27 14:03:55 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char	*g_map;

int		is_spe_carac(char *str, int i)
{
	if (str[i] == 36)
		return (0);
	if (str[i] >= 32 && str[i] <= 47)
		return (1);
	if (str[i] >= 58 && str[i] <= 64)
		return (1);
	if (str[i] == 91 || (str[i] >= 93 && str[i] < 96))
		return (1);
	if (str[i] >= 123 && str[i] <= 126)
		return (1);
	return (0);
}

int		nb_del_case(char *str, int *p_i)
{
	if (str[*p_i] == '\\' && g_map[*p_i] != '1')
	{
		if (str[(*p_i + 1)] == '"' || str[(*p_i + 1)] == '\'')
			return (0);
		if (is_spe_carac(str, *p_i + 1) && g_map[*p_i] == '2')
			return (0);
		if (!is_esc(str, *p_i))
			return (1);
		return (0);
	}
	return (0);
}

int		nb_to_del(char *str)
{
	int	i;
	int	sum;
	int	nb;

	i = 0;
	sum = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '\\' && g_map[i] != '1')
			nb = nb_del_case(str, &i);
		sum += nb;
		nb = 0;
		i++;
	}
	return (sum);
}

char	*clear_it(char *str)
{
	int		nb;
	int		i;
	char	*res;

	i = 0;
	nb = nb_to_del(str);
	{
		if (!(res = malloc(ft_strlen(str) - nb + 1)))
			ft_error('\0', "Malloc", NULL);
		nb = 0;
		while (str[i])
		{
			if (!nb_del_case(str, &i))
				res[nb++] = str[i];
			i++;
		}
		res[nb] = '\0';
	}
	free_str(&str);
	return (res);
}

void	clear_backslash(void)
{
	int	i;

	i = 0;
	g_map = map_quote(lst->cmd, 0);
	if (nb_to_del(lst->cmd))
		lst->cmd = clear_it(lst->cmd);
	free_str(&g_map);
	while (lst->arg[i])
	{
		g_map = map_quote(lst->arg[i], 0);
		if (nb_to_del(lst->arg[i]))
			lst->arg[i] = clear_it(lst->arg[i]);
		free_str(&g_map);
		i++;
	}
	i = 0;
	while (lst->raw[i])
	{
		g_map = map_quote(lst->raw[i], 0);
		if (nb_to_del(lst->raw[i]))
			lst->raw[i] = clear_it(lst->raw[i]);
		free_str(&g_map);
		i++;
	}
}
