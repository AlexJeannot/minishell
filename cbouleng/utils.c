/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:38:58 by cbouleng          #+#    #+#             */
/*   Updated: 2020/03/11 15:39:02 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_esc(char *str, int i)
{
	if (str[i - 1] == '\\')
		return (1);
	return (0);
}

int	ft_exit(int status)
{
	exit(status);
}

void	prompt()
{
	write(1, "$ ", 2);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

static char*	rm_void_quote(char *str, int i)
{
	char*	res;
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (!(res = malloc(ft_strlen(str) - 1)))
		ft_exit(1);
	while (str[j])
	{
		if (j != i && j != i + 1)
			res[k++] = str[j];
		j++;
	}
	res[k] = '\0';
	return (res);
}

char*	clean_void_quote(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && str[i + 1] == '"'
			&& (map_d[i] == '2' || map_d[i + 1] == '2'))
		{
			str = rm_void_quote(str, i);
			map_quote(str);
		}
		if (str[i] == '\'' && str[i + 1] == '\''
			&& (map_s[i] == '1' || map_s[i + 1] == '1'))
		{
			str = rm_void_quote(str, i);
			map_quote(str);
		}
		i++;
	}
	return (str);
}
