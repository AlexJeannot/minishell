/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 16:44:41 by cbouleng          #+#    #+#             */
/*   Updated: 2020/06/20 13:18:21 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char	*g_map;

int		find_rdc(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && !is_esc(str, i) && g_map[i] == '0')
			return (1);
		i++;
	}
	return (0);
}

int		count_rdc(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (g_map[i] == '0' && !is_esc(str, i))
		{
			if (str[i] == '>' && str[i + 1] == '>')
				nb++;
			else if (str[i] == '>' && str[i - 1] != '>')
				nb++;
		}
		i++;
	}
	return (nb);
}

int		is_rdc(char *str, int i)
{
	if (!is_esc(str, i) && g_map[i] == '0')
	{
		if (str[i] == '>' && str[i + 1] == '>')
			return (2);
		if (str[i] == '>' && str[i - 1] != '>')
			return (1);
	}
	return (0);
}

t_cont	init_cont(char *str)
{
	t_cont cont;

	cont.rdc_type = 0;
	cont.rdc_filetab = NULL;
	cont.rdc_filename = NULL;
	cont.rdo_type = 0;
	cont.rdo_filetab = NULL;
	cont.rdo_filename = NULL;
	cont.rdc_index = create_index_array(str, "rdc");
	cont.rdo_index = create_index_array(str, "rdo");
	get_rd_index(str, cont.rdc_index, cont.rdo_index, g_map);
	return (cont);
}

t_cont	get_redir(char *str)
{
	t_cont cont;

	g_map = map_quote(str);
	cont = init_cont(str);
	if (find_rdc(str))
	{
		cont.rdc_filetab = get_rdc_filetab(str);
		cont.rdc_filename = get_last(cont.rdc_filetab);
		cont.rdc_type = get_rdc_type(str);
	}
	if (find_rdo(str))
	{
		free_str(&g_map);
		cont.rdo_filetab = get_rdo_filetab(str);
		cont.rdo_filename = get_last(cont.rdo_filetab);
		cont.rdo_type = 1;
	}
	free_str(&g_map);
	return (cont);
}
