/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 17:13:15 by cbouleng          #+#    #+#             */
/*   Updated: 2020/05/25 17:15:18 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	is_valid(char *stock)
{
	int i;

	i = 0;
	while (stock[i])
	{
		if (stock[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	is_pipe(char *stock)
{
	int	i;

	i = 0;
	while (stock[i])
	{
		if (stock[i] == '|' && !is_esc(stock, i))
			return (1);
		i++;
	}
	return (0);
}
