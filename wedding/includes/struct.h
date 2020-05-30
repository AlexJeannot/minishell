#ifndef STRUCT_H
# define STRUCT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <signal.h>
#include <sys/wait.h>
# include <sys/stat.h>
# include <time.h>
# include "../gnl/get_next_line.h"

typedef	enum
{
	false,
	true
}		bool;

typedef struct		s_cont
{
	int		pipe;
	int		rdo_type;
	int		rdc_type;
	char**	raw;
	char**	rdc_filetab;
	char**	rdo_filetab;
	char**	arg;
	char*	cmd;
	char*	rdc_filename;
	char*	rdo_filename;
	int*	rdc_index;
	int*	rdo_index;
}					t_cont;

typedef struct		s_value
{
	char	*value;
	char	*name;
	int		i;
	int		j;
	int		y;
}					t_value;

typedef struct		s_dolls
{
	char	*value;
	char 	*endline;
	char 	*startline;
	int		len;
}					t_dolls;

typedef struct		s_list
{
	char*			cmd;
	char**			arg;
	char**			raw;
	int				pipe;
	int				rdc_type;
	int				rdo_type;
	char**			rdc_filetab;
	char**			rdo_filetab;
	char*			rdc_filename;
	char*			rdo_filename;
	int*			rdc_index;
	int*			rdo_index;
	struct s_list*	next;
}					t_list;

t_list* lst;
char	**global_env;
t_list *lst_free;

int     ft_strcmp(char *s1, char *s2);
void	clear_lst();
void	parsing(char *line);
void	get_dollar(void);
void	clear_before_exec(void);
void	print_lst(void);
int		ft_strlen(const char *str);
int		is_esc(char *str, int i);
char*	map_quote(char *str, int pos);
void	ft_error_rd(char* msg, char symbol);
void	free_lst(void);



char	**duplicate_array(char **input_array, char **free_array, char sep);
void 	ft_exit(int status);
void 	ft_error(char symbol, char *cmd, char *msg);
void 	free_str(char **str);
void 	free_str_array(char **input_array);
void 	free_int_array(int *input_array);
char	*ft_strdup(const char *input_str);

#endif
