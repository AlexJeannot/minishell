/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 15:42:58 by cbouleng          #+#    #+#             */
/*   Updated: 2020/05/25 15:43:00 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static char		*r_cmd_dollar(int i, char *free_elem)
{
	t_dolls dls;
	char	*res;
	int		j;

	dls = dolls_cmd_value(i);
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

static int		quote_cmd_stop(int i)
{
	int	k;

	k = i;
	while (lst->cmd[i] != '\'' && lst->cmd[i])
		i--;
	while (lst->cmd[k] != '\'' && lst->cmd[k])
		k++;
	if (lst->cmd[k] == '\'' && lst->cmd[i] == '\'')
		return (1);
	return (0);
}

void			get_cmd_dollar(void)
{
	int	i;

	i = 0;
	while (lst->cmd[i])
	{
		if (lst->cmd[i] == '$' && !quote_cmd_stop(i) && !is_esc(lst->cmd, i))
		{
			if (is_env(lst->cmd, i))
				lst->cmd = r_cmd_dollar(i, lst->cmd);
		}
		i++;
	}
}
