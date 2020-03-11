/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 14:36:33 by cbouleng          #+#    #+#             */
/*   Updated: 2020/03/11 16:10:13 by cbouleng         ###   ########.fr       */
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

t_list 			*lst;
int				get_next_line(int fd, char **line);
int				ft_strlen(char *str);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_substr(char *str, int start, int len);
char			**split_plus(char *str, char charset);
char			**clean_esc_quote(char **stk);
void			print_lst(void);
int				ft_exit(int status);
void			prompt();
int				check_quote(char *line);
char			**clean_esc_quote(char **stk);
t_list			*new_lst(void);
bool			is_empty_lst();
int				is_valid(char *stock);
void			del_first(void);
void			clear_lst();
void			list_it(char **stock);
int				is_escaped(char *str, int i);
char			*map_double_quote(char *str);
char			*map_simple_quote(char *str);
