/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 10:37:54 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/06 19:03:28 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	cmp;

	cmp = 0;
	while (s[cmp])
	{
		ft_putchar_fd(s[cmp], fd);
		cmp++;
	}
}
