/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 12:40:54 by cbouleng          #+#    #+#             */
/*   Updated: 2020/06/02 12:47:40 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_dolls		dolls_value(char *str, int j)
{
	t_dolls dls;

	dls.value = get_env_value_2(str, j);
	dls.startline = get_startline(str, j);
	dls.endline = get_endline(str, j);
	dls.len = ft_strlen(dls.value) + ft_strlen(dls.startline)
		+ ft_strlen(dls.endline);
	return (dls);
}

char		*r_dollar(char *str, int j)
{
	t_dolls dls;
	char	*res;
	int		i;

	dls = dolls_value(str, j);
	if (!(res = malloc(dls.len + 1)))
		ft_error('\0', "Malloc", NULL, 1);
	i = 0;
	while (dls.startline[i])
	{
		res[i] = dls.startline[i];
		i++;
	}
	j = 0;
	while (dls.value[j])
		res[i++] = dls.value[j++];
	j = 0;
	while (dls.endline[j])
		res[i++] = dls.endline[j++];
	res[i] = '\0';
	free_str(&str);
	free_str(&dls.value);
	free_str(&dls.startline);
	free_str(&dls.endline);
	return (res);
}

char		*get_dollar_str(char *str)
{
	int		j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '$' && !quote_stop(str, j)
				&& !is_esc(str, j))
		{
			if (is_env(str, j))
				str = r_dollar(str, j);
		}
		j++;
	}
	return (str);
}

char		**get_dollar_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		tab[i] = get_dollar_str(tab[i]);
		i++;
	}
	return (tab);
}

void		get_dollar(void)
{
	if (lst->cmd)
	{
		lst->cmd = get_dollar_str(lst->cmd);
		lst->arg = get_dollar_tab(lst->arg);
		lst->raw = get_dollar_tab(lst->raw);
	}
	if (lst->rdc_filetab)
		lst->rdc_filetab = get_dollar_tab(lst->rdc_filetab);
	if (lst->rdo_filetab)
		lst->rdo_filetab = get_dollar_tab(lst->rdo_filetab);
}
