/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:00:24 by ajeannot          #+#    #+#             */
/*   Updated: 2019/11/29 20:02:59 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);
char	*ft_join(char *str_1, char *str_2, int len_1, int len_2);
int		ft_len(char *str);
char	*ft_dup(const char *str, int len, void *free_str);
int		ft_search(char *str);
char	*ft_settle(char *str, int pass);
int		ft_id(char *str);

/* MANAGE_ERROR.C*/
void    ft_error(char symbol, char *cmd, char *msg);
#endif
