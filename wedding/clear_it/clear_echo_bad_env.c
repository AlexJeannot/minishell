/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_echo_bad_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 14:11:37 by cbouleng          #+#    #+#             */
/*   Updated: 2020/06/02 12:40:24 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char			*g_map;

static int		dollar_to_del_len(char *str, int i, int ret)
{
	int len;

	len = 0;
	if (ret == 2)
		return (1);
	while (str[i] != ' ' && str[i])
	{
		i++;
		len++;
	}
	return (len);
}

static char		*remove_dollar(char *str, int i, int ret)
{
	int		len;
	int		j;
	char	*res;

	g_map = map_quote(str, 0);
	len = dollar_to_del_len(str, i, ret);
	if (!(res = malloc(ft_strlen(str) - len + 1)))
		ft_error('\0', "Malloc", NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && ret == 1)
			while (str[i] != ' ' && str[i])
				i++;
		else if (str[i] == '$' && ret == 2)
			i++;
		res[j++] = str[i++];
	}
	res[j] = '\0';
	free_str(&g_map);
	return (res);
}

int				remove_it(char *str, int i)
{
	if (str[i] == '$' && !is_esc(str, i))
	{
		if (g_map[i] == '1')
			return (0);
		if (!str[i + 1])
			return (0);
		if (str[i + 1] == '\'' || str[i + 1] == '"')
			return (2);
		if (str[i + 1] > 31 && str[i + 1] < 47)
			return (0);
		if (str[i + 1] > 57 && str[i + 1] < 65)
			return (0);
		if (str[i + 1] > 90 && str[i + 1] < 97)
			return (0);
		if (str[i + 1] > 122 && str[i + 1] < 127)
			return (0);
		if (!is_env(str, i))
			return (1);
	}
	return (0);
}

char			*clear_echo_bad_env(char *str)
{
	char	*res;
	int		i;
	int		ret;

	i = 0;
	res = NULL;
	g_map = map_quote(str, 0);
	while (str[i])
	{
		if ((ret = remove_it(str, i)))
		{
			free_str(&g_map);
			res = remove_dollar(str, i, ret);
		}
		i++;
	}
	free_str(&g_map);
	if (res)
	{
		free_str(&str);
		return (res);
	}
	return (str);
}
