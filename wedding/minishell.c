/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:21:45 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/09 19:45:50 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

pid_t ft_create_child(void)
{
    pid_t pid;

    pid = fork();
    return (pid);
}

void ft_exit(char **free_split, int status)
{
    if (free_split)
        free_str_array(free_split);
    clear_lst();
    free_str_array(filtered_env);
    free_str_array(global_env);

    system("leaks minishell");
    exit(status);
}

void send_env(int *fd)
{
    int count;
    int str_len;
    char *str_env;

    count = 0;
    str_len = 0;
    while (global_env[count])
    {
        str_len += ft_strlen(global_env[count]);
        str_len++;
        count++;
    }
    str_env = (char *)malloc(sizeof(char) * str_len);
    count = 0;
    while (global_env[count])
    {
        str_env = ft_strcat(str_env, global_env[count]);
        str_env = ft_strcat(str_env, "\n");
        count++;
    }
    str_env[ft_strlen(str_env) - 1] = '\0';
    write(fd[1], str_env, ft_strlen(str_env));
    free(str_env);
}

void receive_env(int *fd)
{
    int ret;
    char buf[101];
    char *str_env;
    char **tab_env;
    char **split_result;

    //printf("ENTREE RECEIVE ENV\n");

    str_env = NULL;
    while ((ret = read(fd[0], buf, 100)) > 0)
	{
		buf[ret] = '\0';
		str_env = ft_join(str_env, buf, ft_len(str_env), ft_len(buf));
        if (ret < 100)
                break ;
	}
    tab_env = ft_split(str_env, '\n');
    global_env = duplicate_array(tab_env, global_env, '\0');
    split_result = ft_split(global_env[search_in_array(global_env, "PWD", '=')], '=');
    chdir(split_result[1]);
    free_str_array(split_result);
    free(str_env);
    free_str_array(tab_env);
    free_str(piped_str);
}

void display_prompt(void)
{
    char *dir;
    char **split_result_1;
    char **split_result_2;
    /*AFFICHAGE DIR*/
    printf("\033[38;5;208m");
    fflush(stdout);


    split_result_1 = ft_split(global_env[search_in_array(global_env, "PWD", '=')], '=');
    split_result_2 = ft_split(split_result_1[1], '/');
    dir = split_result_2[array_length(split_result_2) - 1];
    write(1, dir, ft_strlen(dir));
    free_str_array(split_result_1);
    free_str_array(split_result_2);
    write(1, " ", 1);

    /*AFFICHAGE PROMPT*/
    printf("\033[38;5;196m");
    fflush(stdout);
    write(1, "}> ", 3);
    printf("\033[0m");
    fflush(stdout);
}

void signal_manager(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        display_prompt();
    }
    if (sig == SIGQUIT)
    {
        if (child_pid > 0)
        {
            write(1, "\n", 1);
            ft_putnbr(child_pid);
            write(1, "      quit", 10);
            write(1, "\n", 1);
            kill(child_pid, SIGKILL);
        }
    }
}

void exec_instructions(t_list *lst)
{
//    printf("ENTREE FCT EXEC INSTRUCTIONS");
    if (ft_strcmp(lst->cmd, "pwd") == 0 || ft_strcmp(lst->cmd, "echo") == 0 || ft_strcmp(lst->cmd, "env") == 0)
        ft_builtins(lst->cmd, lst->raw);
    else if (ft_strcmp(lst->cmd, "cd") == 0)
        ft_cd(lst->arg);
    else if (ft_strcmp(lst->cmd, "export") == 0)
        ft_export(lst->arg);
    else if (ft_strcmp(lst->cmd, "unset") == 0)
        ft_unset(lst->arg);
    else if (ft_strcmp(lst->cmd, "exit") != 0)
        ft_program(lst->cmd, lst->raw);
//    printf("SORTIE FCT EXEC INSTRUCTIONS\n");
}

void set_pipe(t_list *lst, int fd[2])
{
    //printf("PRE DUP 2 SET PIPE FCT");
    dup2(fd[1], STDOUT_FILENO);
    //printf("PRE EXEC INSTRUCTIONS SET PIPE FCT");
    exec_instructions(lst);
}

void receive_pipe(int fd[2])
{
    int		ret;
    char    buf[101];
    struct	stat sb;

    fstat(fd[0], &sb);
    if (sb.st_size > 0)
    {
        while ((ret = read(fd[0], buf, 100)) > 0)
    	{
    		buf[ret] = '\0';
    		piped_str = ft_join(piped_str, buf, ft_len(piped_str), ft_len(buf));
            if (ret < 100)
                    break ;
    	}
    }
}

int is_builtins(char *cmd)
{
    if ((ft_strcmp(cmd, "echo") == 0)
        || (ft_strcmp(cmd, "pwd") == 0)
        || (ft_strcmp(cmd, "env") == 0))
        return (1);
    return (0);
}

void display_list(t_list *lst)
{
    t_list *browse;
    int i;

    i = 0;
    browse = lst;
    while (browse)
    {
        printf("================ ELEM %d ================\n", i);
        printf("CMD = %s\n", browse->cmd);
        printf("------- start args -------\n");
        display_array(browse->arg);
        printf("------- end args -------\n");
        printf("pipe = %d\n", browse->pipe);
        browse = browse->next;
        i++;
    }
}

void free_str(char *str)
{
    if (str)
    {
        free(str);
        str = NULL;
    }
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    char *line;
    int ret_gnl;
    int fd[2];

    global_env = duplicate_array(env, NULL, '\0');
    filtered_env = filter_env(global_env, NULL);

    signal(SIGINT, signal_manager);
    signal(SIGQUIT, signal_manager);
    while (1)
    {
        free_str(piped_str);
        display_prompt();
        pipe(fd);
        ret_gnl = get_next_line(0, &line);
        if (line && line[0])
        {
            parsing(line);
            while (lst)
            {
				//ici get_dollar();
				//ici clean_quote();
                child_pid = ft_create_child();

                if (child_pid == 0)
                {
                    if (lst->pipe == 1)
                        set_pipe(lst, fd);
                    else
                    {
                        exec_instructions(lst);
                        send_env(fd);
                    }
                    return (0);
                }
                else
                {
                    wait(NULL);
                    if (lst->pipe == 1)
                        receive_pipe(fd);
                    else
                        if (!(is_builtins(lst->cmd)))
                            receive_env(fd);
                    if (ft_strcmp(lst->cmd, "exit") == 0)
                        ft_exit(NULL, 1);
                    filtered_env = filter_env(global_env, filtered_env);
                }
                lst = lst->next;
            }
        }
        else if (ret_gnl == 0)
            ft_exit(NULL, 1);
        free(line);
    	clear_lst();
        free(piped_str);
        child_pid = -1;
    }
}
