#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "../get_next_line/get_next_line.h"

# define KO -1
# define OK 1

/* VARIABLES GLOBALES */
char **global_env;
char **init_env_var;

/* DISPLAY_STRING */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

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
void ft_cd(char *args);

/* EXEC_EXPORT */
char    **sort_env(void);
int     is_valid_var(char *str);
int     is_valid_value(char *str);
int     find_special_car(char *str);
void    ft_export(char *args);

/* EXEC_BUILTINS */
void ft_builtins(char *args);

/* EXEC_PROGRAM */
void ft_program(char *args);

/* EXEC_UNSET */
int     is_deleted(int *tab_index, int index);
char    **cleared_env(char **from_array, char **output_array, int *tab_index);
void    ft_unset(char *args);

/* MANAGE_ARRAY */
int     array_length(char **input_array);
char    **duplicate_array(char **input_array, char **free_array, char sep);
char    **sort_array(char **input_array);
void    free_str_array(char **input_array);
int     search_in_array(char **input_array, char* str, char sep);
void    display_array(char **input_array);
char    **extend_array(char **from_array, char **add_array, int from_len, int add_len);

/* MANAGE_ENV */
char    *get_env_value(char *var);

/* MANAGE_STRING */
int     find_car(char *str, char c);
int     ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char	*ft_strcat(char *dest, char *src);
char	*ft_strncat(char *dest, char *src, unsigned int nb);
int     ft_strcmp(char *s1, char *s2);

/* MINISHELL */
pid_t   ft_create_child(void);
void    ft_exit(char **free_split);

#endif
