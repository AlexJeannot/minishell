/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_raw_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 16:36:17 by cbouleng          #+#    #+#             */
/*   Updated: 2020/05/25 16:36:52 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static char		*r_dollar(int i, int j, char *free_elem)
{
	t_dolls dls;
	char	*res;

	dls = raw_dolls_value(i, j);
	if (!(res = malloc(dls.len + 1)))
		ft_error('\0', "Malloc", NULL);
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
	free_str(&free_elem);
	free_str(&dls.value);
	free_str(&dls.startline);
	free_str(&dls.endline);
	return (res);
}

static int		quote_stop(int i, int j)
{
	int	k;

	k = j;
	while (lst->raw[i][j] != '\'' && lst->raw[i][j])
		j--;
	while (lst->raw[i][k] != '\'' && lst->raw[i][k])
		k++;
	if (lst->raw[i][k] == '\'' && lst->raw[i][j] == '\'')
		return (1);
	return (0);
}

void			get_raw_dollar(void)
{
	int	i;
	int	j;

	i = 0;
	while (lst->raw[i])
	{
		j = 0;
		while (lst->raw[i][j])
		{
			if (lst->raw[i][j] == '$' && !quote_stop(i, j)
				&& !is_esc(lst->raw[i], j))
			{
				if (is_env(lst->raw[i], j))
					lst->raw[i] = r_dollar(i, j, lst->raw[i]);
			}
			j++;
		}
		i++;
	}
}
