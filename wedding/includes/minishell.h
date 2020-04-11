#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
#include <sys/types.h>
# include "../gnl/get_next_line.h"
# include <signal.h>
#include <sys/stat.h>
#include <time.h>

# define KO -1
# define OK 1

/* VARIABLES GLOBALES */
char **global_env;
char **filtered_env;
int errno;
pid_t child_pid;
char *piped_str;

/* DISPLAY_STRING */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void 	ft_putnbr_annex(int nb);
void 	ft_putnbr(int nb);


/* FT_SPLIT */
//static int		ft_cmp_string(char const *s, char c);
//static char		*ft_create_string(char const *s, int nb_car);
//static char		**ft_sep_string(char const *s, char c, char **total_string);
char			**ft_split(char const *s, char c);

/* EXEC_CD */
void update_env(char *new_path);
char *previous_dir(void);
char *relative_path(char *input_path);
char *absolute_path(char *input_path);
void ft_cd(char **args);

/* EXEC_EXPORT */
char    **sort_env(void);
int     is_valid_var(char *str);
int     is_valid_value(char *str);
int     find_special_car(char *str);
void    ft_export(char **args);


/* EXEC_PROGRAM */


/* EXEC_UNSET */
int is_unset(int *index_array, int index);
char **clear_env(char **input_array, int *index_array);
int *create_unset_index_array(char **input_array);
void ft_unset(char **args);


/* MANAGE_ARRAY */
int     array_length(char **input_array);
int 	int_array_length(int *input_array);
char    **duplicate_array(char **input_array, char **free_array, char sep);
char    **sort_array(char **input_array);
void    free_str_array(char **input_array);
int     search_in_array(char **input_array, char* str, char sep);
void    display_array(char **input_array);
char    **extend_array(char **from_array, char **add_array, int from_len, int add_len);
char 	**filter_env(char **input_array, char** free_array);

/* MANAGE_ENV */
char    *get_env_value(char *var);

/* MANAGE_ERROR */
void display_error(char *exec, char *error_str);

/* MANAGE_STRING */
int     find_car(char *str, char c);
int     ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char	*ft_strcat(char *dest, char *src);
char	*ft_strncat(char *dest, char *src, unsigned int nb);
int     ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
void 	free_str(char *str);



/* MINISHELL */
pid_t   ft_create_child(void);
void    ft_exit_2(char **free_split, int status);


/* Charles */
typedef	enum
{
	false,
	true
}		bool;

typedef struct		s_cont
{
	int		pipe;
	char*	cmd;
	char**	raw;
	int		rdc_type;
	int		rdo_type;
	char**	rdc_filetab;
	char**	rdo_filetab;
	char*	rdc_filename;
	char*	rdo_filename;
	char**	arg;
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

/*              #string
-------------------------------------------------*/
int				ft_strcmp(char *s1, char *s2);
char*			ft_strjoin(char *s1, char *s2);
char*			ft_substr(char *str, int start, int len);
char**			split_plus(char *str, char charset);

t_list*			lst;
char**			global_env;

/*              #backslash
-------------------------------------------------*/
int				is_esc(char *str, int i);
void			clear_backslash(void);

/*              #quote
-------------------------------------------------*/
int				check_quote(char *str);
char*			map_quote(char *str, int pos);

/*              #chained_list
-------------------------------------------------*/
void			print_lst(void);
t_list			*new_lst(void);
bool			is_empty_lst();
void			del_first(void);
void			clear_lst();
void			list_it(char **stock);
int				is_valid(char *stock);

/*              #dollar
-------------------------------------------------*/
void			get_dollar(void);
void			get_cmd_dollar(void);
int				is_path(char *str);
int				ft_envcmp(char *s1, char *s2);
int				is_env(char *str, int j);
t_value			new_value(int i, int j);
char*			get_env_name_2check(char *str, int j);
char*			get_lil_path_value(t_value v);
char*			get_env_value_2(int i, int j);
char*			get_startline(int i, int j);
char*			get_endline(int i, int j);
char*			clear_echo_bad_env(char* str);

/*              #redir
-------------------------------------------------*/
t_cont			get_redir(char* str);
char**			get_rdo_filetab(char* str);
int				find_rdo(char* str);
int				is_name(char* str, int i);
char*			get_name(char* str, int i, int ret);
char*			clear_stock_rd(char* str);

/*              #check
-------------------------------------------------*/
void			check(char* line);
void			check_simple_quote(char* str);
void			check_double_quote(char* str);
void			check_bs(char* str);
void			check_rdc(char* str);
void			check_rdo(char* str);

/*              #utils
-------------------------------------------------*/
void			prompt();
int				ft_exit(char* msg, int status);
int				ft_exit_rd(char* msg, char symbol);
int				get_next_line(int fd, char **line);
void			clear_before_print(void);
int				ft_tablen(char **tab);
void			defrag_arg(int len);

/*              #main
-------------------------------------------------*/
int	parsing(char *line);

/* MANAGE_REDIRECTION */
void 	set_redirection(t_list *lst, int fd[2]);
void    receive_redirection(t_list *lst, int fd[2]);
int    check_rdo_exec(t_list *lst);

void exec_instructions(t_list *lst);
void ft_program(t_list *lst, char *cmd, char **args);

/* EXEC_BUILTINS */
void ft_builtins(t_list *lst, char *cmd, char **args);

void display_int_array(int *input_array);
int		count_rdo(char* str);

#endif
