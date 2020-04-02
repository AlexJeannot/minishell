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

typedef struct		s_cont
{
	int		pipe;
	char*	cmd;
	int		rdc_type;
	int		rdo_type;
	char**	rdc_filetab;
	char**	rdo_filetab;
	char*	rdc_filename;
	char*	rdo_filename;

	char**	arg;
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
	char*			rd_filename;
	int				rd_type;
	char**			arg;
	int				pipe;
	struct s_list*	next;
}					t_list;

/*              #string
-------------------------------------------------*/
int				ft_strlen(char *str);
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
char*			get_env_value(int i, int j);
char*			get_startline(int i, int j);
char*			get_endline(int i, int j);
char*			clear_echo_bad_env(char* str);


/*              #utils
-------------------------------------------------*/
void			prompt();
int				ft_exit(int status);
int				get_next_line(int fd, char **line);
void			clear_before_print(void);
int				ft_tablen(char **tab);
void			defrag_arg(int len);
