/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:12:58 by cbouleng          #+#    #+#             */
/*   Updated: 2020/03/10 16:38:47 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>

char	*map_d;
char	*map_s;

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*map_double_quote(char *str)
{
	char	*map_d;
	int 	i;

	i = ft_strlen(str);
	if (!(map_d = malloc(i + 1)))
		exit(1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			map_d[i++] = '1';
			while (str[i] != '"')
				map_d[i++] = '1';
			map_d[i++] = '1';
		}
		map_d[i] = '0';
		i++;
	}
	map_d[i] = '\0';
	return (map_d);
}

char	*map_simple_quote(char *str)
{
	char	*map_s;
	int 	i;

	i = ft_strlen(str);
	if (!(map_s = malloc(i + 1)))
		exit(1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			map_s[i++] = '2';
			while (str[i] != '\'')
				map_s[i++] = '2';
			map_s[i++] = '2';
		}
		map_s[i] = '0';
		i++;
	}
	map_s[i] = '\0';
	return (map_s);
}

int		sep(char c, int i, char charset)
{
	if (c == charset && map_s[i] == '0' && map_d[i] == '0')
		return (1);
	return (0);
}

int		set_sep(char *str, char charset)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && !sep(str[i], i, charset))
			i++;
		if (str[i] && sep(str[i], i, charset))
		{
			count++;
			i++;
			while (str[i] && !sep(str[i], i, charset))
				i++;
		}
	}
	return (count);
}

char	*finder(char *str, int i, char charset)
{
	char	*part;
	int		j;
	int		ibis;

	ibis = i;
	while (str[i] && !sep(str[i], i, charset))
		i++;
	if (!(part = malloc(i + 1)))
		return (NULL);
	i = ibis;
	while (str[i] == ' ')
		i++;
	j = 0;
	while (str[i] && !sep(str[i], i, charset))
		part[j++] = str[i++];
	part[j] = '\0';
	printf("%s\n", part);
	return (part);
}

char	**ft_split_plus_2(char *str, char charset)
{
	int		i;
	int		j;
	char	**tab;

	map_d = map_double_quote(str);
	map_s = map_simple_quote(str);
	i = set_sep(str, charset);
	tab = malloc((i + 1) * sizeof(char*));
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && !sep(str[i], i, charset))
			i++;
		if (str[i] && sep(str[i], i, charset))
		{
			tab[j++] = finder(str, i, charset);
			while (str[i] && !sep(str[i], i, charset))
				i++;
		}
	}
	tab[j] = NULL;
	return (tab);
}
