/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:33:00 by cbouleng          #+#    #+#             */
/*   Updated: 2020/03/05 14:37:34 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		both;
	char	*res;

	i = 0;
	both = ft_strlen(s1) + ft_strlen(s2);
	if (!(res = malloc(both + 1)))
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	free(s1);
	return (res);
}

char	*ft_substr(char *str, int start, int len)
{
	int		i;
	char	*res;

	if (!(res = malloc(len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = str[start];
		start++;
		i++;
	}
	res[i] = '\0';
	return (res);
}
