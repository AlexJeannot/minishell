#ifndef PARSING_H
# define PARSING_H

# include "./struct.h"

/*              #string
-------------------------------------------------*/
char*			ft_strjoin(char *s1, char *s2);
char*			ft_substr(char *str, int start, int len);
char**			split_plus(char *str, char charset);

/*              #backslash
-------------------------------------------------*/
void			clear_backslash(void);

/*              #quote
-------------------------------------------------*/
int				check_quote(char *str);
char			*clear_quote(char *str);

/*              #chained_list
-------------------------------------------------*/
t_list			*new_lst(void);
bool			is_empty_lst();
void			list_it(char **stock);
int				is_valid(char *stock);
int				is_pipe(char *stock);

/*              #dollar
-------------------------------------------------*/
void			get_raw_dollar(void);
void			get_cmd_dollar(void);
t_dolls			dolls_cmd_value(int i);
t_dolls			raw_dolls_value(int i, int j);
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
int				find_rdc(char* str);
int				is_name(char* str, int i);
int				is_rdc(char *str, int i);
char*			get_name(char* str, int i, int ret);
char*			clear_stock_rd(char* str);
int		        count_rdo(char* str);
int		        count_rdc(char* str);
void			get_rd_index(char *str, int *rdc_index, int *rdo_index, char *g_map);
int				*create_index_array(char *str, char *type);
int				is_name(char *str, int i);
char			*get_name(char *str, int i, int ret);
char			*get_rdc_name(char *str, int i);
char			**get_rdc_filetab(char *str);
int				get_rdc_type(char *str);

/*              #check
-------------------------------------------------*/
void			check(char* line);
void			check_rdc(char* str, char* map);
void			check_rdo(char* str, char* map);

/*              #utils
-------------------------------------------------*/
void			prompt();
int				get_next_line(int fd, char **line);
int				ft_tablen(char **tab);
void			defrag_arg(int len);
char			*get_last(char** tab);
int				count_valid_str(char **input_array);
char			**clean_array(char **input_array);
char			*clean_cmd(char *input_str);
void			clear_tab(char ***pt_tab);
void			clear_str(char **pt_str);

#endif
