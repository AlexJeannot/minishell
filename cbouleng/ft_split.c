/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 09:55:12 by cbouleng          #+#    #+#             */
/*   Updated: 2020/03/06 10:04:57 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char set)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == set)
			s++;
		if (*s && *s != set)
		{
			count++;
			while (*s && *s != set)
				s++;
		}
	}
	return (count);
}

static char	*finder(char const *s, char c)
{
	char	*tab;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!(tab = malloc(i + 1)))
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

static void	*ft_freeall(char **tab, int i)
{
	while (i)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	int		count;
	char	**tab;
	int		i;

	count = count_words(s, c);
	if (!(tab = malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			if (!(tab[i] = finder(s, c)))
				return (ft_freeall(tab, i - 1));
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	tab[i] = NULL;
	return (tab);
}
