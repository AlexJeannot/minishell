#ifndef PARSING_H
# define PARSING_H

# include "./struct.h"

/*              #string
-------------------------------------------------*/
//int				ft_strcmp(char *s1, char *s2);
char*			ft_strjoin(char *s1, char *s2);
char*			ft_substr(char *str, int start, int len);
char**			split_plus(char *str, char charset);

/*              #backslash
-------------------------------------------------*/
void			clear_backslash(void);

/*              #quote
-------------------------------------------------*/
int				check_quote(char *str);

/*              #chained_list
-------------------------------------------------*/
//void			print_lst(void);
t_list			*new_lst(void);
bool			is_empty_lst();
void			del_first(void);
//void			clear_lst();
void			list_it(char **stock);
int				is_valid(char *stock);

/*              #dollar
-------------------------------------------------*/
void			get_raw_dollar(void);
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
int		        count_rdo(char* str);

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
//void			clear_before_print(void);
int				ft_tablen(char **tab);
void			defrag_arg(int len);

/*              #main
-------------------------------------------------*/
//int	parsing(char *line);

#endif
