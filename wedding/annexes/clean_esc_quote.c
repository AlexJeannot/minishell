/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_esc_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:29:07 by cbouleng          #+#    #+#             */
/*   Updated: 2020/03/11 15:42:30 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		is_esc(char *str, int i)
{
	if (str[i] == '\\' && (str[i + 1] == '"' || str[i + 1] == '\''))
		return (1);
	i++;
	return (0);
}

static int		spot_esc(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_esc(str, i))
			return (1);
		i++;
	}
	return (0);
}

static char		*rm_slash(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	if (!(tmp = malloc(ft_strlen(str))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!is_esc(str, i))
			tmp[j++] = str[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char		**clean_esc_quote(char **stk)
{
	char	*tmp;
	int		i;

	i = 0;
	while (stk[i])
	{
		if (spot_esc(stk[i]))
		{
			tmp = rm_slash(stk[i]);
			free(stk[i]);
			stk[i] = tmp;
		}
		i++;
	}
	return (stk);
}
