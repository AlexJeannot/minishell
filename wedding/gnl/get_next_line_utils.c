/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:00:36 by ajeannot          #+#    #+#             */
/*   Updated: 2019/11/30 15:50:24 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_len(char *str)
{
	int cmp;

	if (!str)
		return (0);
	cmp = 0;
	while (str[cmp])
		cmp++;
	return (cmp);
}

char	*ft_dup(const char *str, int len, char *str_free)
{
	char	*new_str;
	int		cmp;

	if (!str)
	{
		if (!(new_str = (char *)malloc(sizeof(char) * 1)))
			ft_error('\0', "Malloc", NULL);
		new_str[0] = '\0';
	}
	else
	{
		if (!(new_str = (char *)malloc(sizeof(char) * (len + 1))))
			ft_error('\0', "Malloc", NULL);
		if (new_str == NULL)
			return (NULL);
		cmp = 0;
		while (cmp < len)
		{
			new_str[cmp] = str[cmp];
			cmp++;
		}
		new_str[cmp] = '\0';
	}
	free_str(&str_free);
	return (new_str);
}

int		ft_search(char *str)
{
	int cmp;

	cmp = 0;
	if (!str)
		return (-1);
	while (str[cmp])
	{
		if (str[cmp] == '\n')
			return (cmp);
		cmp++;
	}
	return (-1);
}

char	*ft_settle(char *str, int pass)
{
	if (str && (pass == 1 || str[0]))
	{
		free(str);
		str = NULL;
	}
	return (str);
}
