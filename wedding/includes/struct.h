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
	int*	rdc_index; // Ajout index rdc
	int*	rdo_index; // Ajout index rdo
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
	int*			rdc_index; // Ajout index rdc
	int*			rdo_index; // Ajout index rdo
	struct s_list*	next;
}					t_list;

t_list* lst;
char	**global_env;

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


/* MANAGE_ARRAY.C */
char	**duplicate_array(char **input_array, char **free_array, char sep);

/* MANAGE_EXIT.C */
void 	ft_exit(int status);

/* MANAGE_ERROR.C */
void 	ft_error(char symbol, char *cmd, char *msg);

/* MANAGE_STR.C */
void 	free_str(char **str);

/* MANAGE_STR_ARRAY.C */
void 	free_str_array(char **input_array);

/* MANAGE_INT_ARRAY.C */
void 	free_int_array(int *input_array);

/* MANAGE_STR_DUP.C */
char	*ft_strdup(const char *input_str);

/* MANAGE_LEAKS */ // ==============> TO DELETE BEFORE EVALUATION
void 	ft_leaks(char *position);

#endif
