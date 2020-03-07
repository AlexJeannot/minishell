/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:39:09 by cbouleng          #+#    #+#             */
/*   Updated: 2020/03/05 14:37:25 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_free(char **line, char **str, int pos)
{
	if (line && *line)
	{
		free(line);
		*line = NULL;
	}
	if (*str && str)
	{
		free(*str);
		*str = NULL;
	}
	return (pos);
}

static int	front(int fd, char **line, char **str)
{
	if (read(fd, 0, 0) == -1 || !line)
		return (0);
	if (!*str)
	{
		if (!(*str = malloc(BUFFER_SIZE + 1)))
			return (0);
	}
	return (1);
}

static int	spot(char *str)
{
	int i;

	i = 0;
	if (str[i] == '\n')
		return (i);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int	track_line(char **line, char **pt_str)
{
	int		len;
	char	*temp;

	if ((len = spot(*pt_str)) >= 0)
	{
		if (!(*line = ft_substr(*pt_str, 0, len)))
			return (ft_free(line, pt_str, -1));
		if (!(temp = ft_substr(*pt_str, len + 1, (ft_strlen(*pt_str) - len))))
			return (ft_free(line, pt_str, -1));
		free(*pt_str);
		*pt_str = temp;
		return (1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	int			rdbytes;
	static char *str;

	if (!(front(fd, line, &str)))
		return (-1);
	if (track_line(line, &str))
		return (1);
	while ((rdbytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[rdbytes] = '\0';
		if (!(str = ft_strjoin(str, buf)))
			return (ft_free(line, &str, -1));
		if (track_line(line, &str))
			return (1);
	}
	if (track_line(line, &str))
		return (1);
	if (!(*line = ft_substr(str, 0, ft_strlen(str))))
		return (ft_free(line, &str, -1));
	return (ft_free(NULL, &str, 0));
}
