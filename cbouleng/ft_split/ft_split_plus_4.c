/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:12:58 by cbouleng          #+#    #+#             */
/*   Updated: 2020/03/11 09:50:45 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>


int		separator(char c, char *charset)
{
	int i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		set_separator(char *str, char *charset)
{
	int count;

	count = 0;
	while (*str)
	{
		while (*str && separator(*str, charset))
			str++;
		if (*str && !separator(*str, charset))
		{
			count++;
			while (*str && !separator(*str, charset))
				str++;
		}
	}
	return (count);
}

char	*finder(char *str, char *charset)
{
	char	*part;
	int		i;
	int		j;

	i = 0;
	while (str[i] && !separator(str[i], charset))
		i++;
	if (!(part = malloc(i + 1)))
		return (NULL);
	i = 0;
	while (str[i] == ' ')
		i++;
	j = 0;
	while (str[i] && !separator(str[i], charset))
		part[j++] = str[i++];
	part[j] = '\0';
	return (part);
}

char	**ft_split_plus(char *str, char *charset)
{
	int		count;
	char	**tab;
	int		i;

	count = set_separator(str, charset);
	tab = (char**)malloc((count + 1) * sizeof(char*));
	i = 0;
	while (*str)
	{
		while (*str && separator(*str, charset))
			str++;
		if (*str && !separator(*str, charset))
		{
			tab[i] = finder(str, charset);
			i++;
			while (*str && !separator(*str, charset))
				str++;
		}
	}
	tab[i] = NULL;
	return (tab);
}
