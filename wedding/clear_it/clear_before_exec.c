/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_before_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 14:04:34 by cbouleng          #+#    #+#             */
/*   Updated: 2020/06/03 14:38:16 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char		*g_map;

static int	nb_del_quote(char *str)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		if (i == 0 && g_map[i] == '4')
			nb++;
		else if (g_map[i] == '3' || g_map[i] == '4')
			nb++;
		else if (g_map[i] == '4' && !g_map[i + 1])
			nb++;
		else if (str[i] == '\\' && str[i + 1] == '"' && g_map[i] != '1')
			nb++;
		i++;
	}
	return (nb);
}

static int	to_print(char *str, int i)
{
	if (g_map[i] == '1')
		return (1);
	if (str[i] == '"' && !str[i + 1] && g_map[i] == '2')
		return (0);
	if (str[i] == '\\' && !is_esc(str, i) && (str[i + 1] == '"'
		|| str[i + 1] == '\'') && g_map[i] == '0')
		return (0);
	if (str[i] == '\\' && str[i + 1] == '"' && str[i + 2])
		return (0);
	if (g_map[i] == '3' || g_map[i] == '4')
		return (0);
	return (1);
}

char		*clear_quote(char *str)
{
	char	*res;
	int		nb;
	int		j;
	int		k;

	g_map = map_quote(str, 1);
	nb = nb_del_quote(str);
	if (!(res = malloc(ft_strlen(str) - nb + 1)))
		ft_error('\0', "Malloc", NULL);
	j = 0;
	k = 0;
	while (str[j])
	{
		if (to_print(str, j))
			res[k++] = str[j];
		j++;
	}
	res[k] = '\0';
	free_str(&g_map);
	free_str(&str);
	return (res);
}

void		clear_before_exec(void)
{
	if (lst->cmd)
		clear_str(&lst->cmd);
	if (lst->arg)
		clear_tab(&lst->arg);
	if (lst->raw)
		clear_tab(&lst->raw);
	if (lst->rdc_filetab)
	{
		clear_tab(&lst->rdc_filetab);
		lst->rdc_filename = get_last(lst->rdc_filetab);
	}
	if (lst->rdo_filetab)
	{
		clear_tab(&lst->rdo_filetab);
		lst->rdo_filename = get_last(lst->rdo_filetab);
	}
	lst->cmd = clean_cmd(lst->cmd);
	lst->arg = clean_array(lst->arg);
	lst->raw = clean_array(lst->raw);
}
