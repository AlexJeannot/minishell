/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 13:20:24 by ajeannot          #+#    #+#             */
/*   Updated: 2019/11/30 15:50:25 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_join(char *str_1, char *str_2, int len_1, int len_2)
{
	int		cmp;
	char	*output_str;

	output_str = (char *)malloc(sizeof(char) * (len_1 + len_2 + 1));
	if (output_str == NULL)
		return (NULL);
	cmp = 0;
	if (str_1)
		while (str_1[cmp])
		{
			output_str[cmp] = str_1[cmp];
			cmp++;
		}
	cmp = 0;
	while (str_2[cmp])
	{
		output_str[cmp + len_1] = str_2[cmp];
		cmp++;
	}
	output_str[cmp + len_1] = '\0';
	if (str_1)
		free(str_1);
	return (output_str);
}

int		ft_error(int fd, char **line)
{
	char	check_str[1];

	if (fd < 0 || !line || read(fd, check_str, 0) == -1)
		return (-1);
	return (1);
}

int		ft_id(char *str)
{
	int cmp;

	cmp = ft_search(str);
	if (cmp == -1)
		cmp = ft_len(str);
	return (cmp);
}

int		get_next_line(int fd, char **line)
{
	static char	*str;
	int			ret;
	char		buf[101];
	int			pass;

	pass = 0;
	if (ft_error(fd, line) == -1)
		return (-1);
	while ((ret = read(fd, buf, 100)) > 0)
	{
		pass = 1;
		buf[ret] = '\0';
		str = ft_join(str, buf, ft_len(str), ft_len(buf));
		if (ft_search(str) != -1)
			break ;
	}
	if (str && str[0] && ft_search(str) != -1)
	{
		*line = ft_dup(str, ft_id(str), NULL);
		str = ft_dup(&str[ft_id(str) + 1], ft_len(&str[ft_id(str) + 1]), str);
		return (1);
	}
	*line = ft_dup(str, ft_id(str), NULL);
	str = ft_settle(str, pass);
	return (0);
}
