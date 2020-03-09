/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 14:36:33 by cbouleng          #+#    #+#             */
/*   Updated: 2020/03/09 15:19:14 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define BUFFER_SIZE 64
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef	enum
{
	false,
	true
}		bool;

typedef struct	s_trio
{
	char	*cmd;
	char	**arg;
	int		pipe;
}				t_trio;

typedef struct	s_list
{
	char			*cmd;
	char 			**arg;
	int				pipe;
	struct s_list 	*next;
}				t_list;

typedef struct	s_uti
{
	int i;
	int j;
}				t_uti;

typedef struct	s_stt
{
	t_list		*lst;
}				t_stt;

int				get_next_line(int fd, char **line);
int				ft_strlen(char *str);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_substr(char *str, int start, int len);
char			**ft_split(char const *s, char c);
char			**ft_split_plus(char *str, char *charset);
