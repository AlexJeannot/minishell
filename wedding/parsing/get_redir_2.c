/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 16:51:48 by cbouleng          #+#    #+#             */
/*   Updated: 2020/05/25 17:02:42 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int		get_rdc_type(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i])
	{
		if (str[i] == '>' && str[i - 1] == '>')
			return (2);
		if (str[i] == '>')
			return (1);
		i--;
	}
	return (0);
}

int		*create_index_array(char *str, char *type)
{
	int	count;
	int	*index_array;

	count = 0;
	if (ft_strcmp("rdc", type) == 0)
		count = count_rdc(str);
	else if (ft_strcmp("rdo", type) == 0)
		count = count_rdo(str);
	if (!(index_array = (int *)malloc(sizeof(int) * (count + 1))))
		ft_error('\0', "Malloc", NULL);
	return (index_array);
}

void	get_rd_index(char *str, int *rdc_index, int *rdo_index, char *g_map)
{
	int i;
	int index;
	int rdc_add;
	int rdo_add;

	i = 0;
	index = 0;
	rdc_add = 0;
	rdo_add = 0;
	while (str[i])
	{
		if (str[i] == '>' && !is_esc(str, i) && g_map[i] == '0')
		{
			rdc_index[rdc_add] = index;
			if (str[i + 1] && str[i + 1] == '>')
				i++;
			index++;
			rdc_add++;
		}
		if (str[i] == '<' && !is_esc(str, i) && g_map[i] == '0')
			rdo_index[rdo_add++] = index++;
		i++;
	}
	rdc_index[rdc_add] = -1;
	rdo_index[rdo_add] = -1;
}
