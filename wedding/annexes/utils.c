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

#include "../includes/minishell.h"
/*
int	ft_exit(int status)
{
	exit(status);
}
*/
void	prompt()
{
	write(1, "$ ", 2);
}

int		check_quote(char *line)
{
	int i;
	int	d;
	int	s;

	i = 0;
	d = 0;
	s = 0;
	while (line[i])
	{
		if (line[i] == '"')
			d++;
		if (line[i] == '\'')
			s++;
		i++;
	}
	if (!(d % 2) && !(s % 2))
		return (1);
	return (0);
}
