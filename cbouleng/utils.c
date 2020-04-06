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
	int nb;
	
	nb = 0;
	if (str[i - 1] == '\\')
	{
		i--;
		while (str[i] == '\\')
		{
			i--;
			nb++;
		}
		if (nb % 2)
			return (1);
	}
	return (0);
}

int	ft_exit(char* msg, int status)
{
	printf("error: %s\n", msg);
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

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
