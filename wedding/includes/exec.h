#ifndef EXEC_H
# define EXEC_H

# include "./struct.h"

/* ------------- VARIABLES GLOBALES ------------- */
int		errno;
pid_t	child_pid;
char	**filtered_env;
int p_fd[2];

/* ------------- ANNEXES ------------- */

/* DISPLAY_STRING.C */
void	ft_putstr_fd(char *str, int fd);
void	ft_putnbr(int nb);

/* FT_SPLIT.C */
char	**ft_split(char const *s, char c);


/* ------------- EXEC ------------- */

/* EXEC_BUILTINS.C */
int     is_builtins(char *cmd);
void ft_builtins(char *exec, char **args);

/* EXEC_CD_MAIN.C */
void	ft_cd(char **args);

/* EXEC_CD_PATH.C */
char	*select_path(char *input_path);

/* EXEC_EXPORT_BACKSLASH.C */
char	*transform_backslash(char *output_str, char *input_str);

/* EXEC_EXPORT_DISPLAY.C */
void	display_exported_env(void);

/* EXEC_EXPORT_ERROR.C */
int		is_valid_var(char *str);
int verify_exported_var(char *input_str);
int verify_exported_array(char **input_array);

/* EXEC_EXPORT_MAIN.C */
int 	ft_export(char **args);

/* EXEC_PROGRAM.C */
void ft_program(char *cmd, char **args);

/* EXEC_UNSET_ERROR.C */
int		verify_unset_var(char **input_array);

/* EXEC_UNSET_MAIN.C */
int	ft_unset(char **args);


/* ------------- MANAGERS ------------- */

/* MANAGE_ARRAY.C */
char	**sort_array(char **input_array);
int		search_in_array(char **input_array, char* str, char sep);
char	**filter_env(char **input_array, char** free_array);

/* MANAGE_ARRAY_EXTEND.C */
char	**extend_array(char **from_array, char **add_array, int from_len, int add_len);

/* MANAGE_ENV.C */
char    *read_from_fd(int fd[2]);
char	*get_env_value(char *var);
int     env_need_update(char *cmd);
void    send_env(int *fd);
void    receive_env(int *fd);

/* MANAGE_EXIT_STATUS.C */
void	replace_exit_status(int status);

/* MANAGE_INT_ARRAY.C */
int		int_array_length(int *input_array);
void	display_int_array(int *input_array);

/* MANAGE_INT.C */
char	*ft_itoa(int nb);

/* MANAGE_PIPE.C */


/* MANAGE_REDIRECTION.C */
void    set_rdo(void);
void    receive_redirection(int fd[2]);

/* MANAGE_STR_ARRAY.C */
int     str_array_length(char **input_array);
void    display_str_array(char **input_array);
void    free_str_array(char **input_array);

/* MANAGE_STR_DUP.C */
char	*ft_strcpy(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, unsigned int limit);
char	*ft_strcat(char *dest, char *src);
char	*ft_strncat(char *dest, char *src, unsigned int limit);

/* MANAGE_STR.C */
int		find_car(char *str, char c);


/* ------------- PRINCIPAL ------------- */

/* MINISHELL_EXEC.C */
void    exec_prompt(void);
int     exec_instructions(void);
void exec_child(int is_prev_piped, int exit_status);
int exec_father(int exit_status);
int exec_command_line(char *line, int exit_status);

/* MINISHELL_QUIT.C */
void    quit_shell_eof(char *line);
void free_command_line(char *line);

/* MINISHELL_SETUP.C */
void    signal_manager(int sig);
void setup_env(char **env, int *exit_status);
void setup_command(int exit_status);


/* NEW */
void setup_pipe_and_process(int exit_status);

#endif
