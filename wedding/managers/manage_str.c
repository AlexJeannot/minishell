/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:17:09 by ajeannot          #+#    #+#             */
/*   Updated: 2020/06/16 17:55:10 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	find_car(char *str, char c)
{
	int count;

	count = 0;
	while (str[count])
	{
		if (str[count] == c)
			return (count);
		count++;
	}
	return (-1);
}

int	ft_strlen(const char *str)
{
	int count;

	count = 0;
	if (str)
	{
		while (str[count])
			count++;
		return (count);
	}
	return (-1);
}

void	free_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}
