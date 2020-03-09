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

void ft_exit(char **free_split)
{
    free_str_array(free_split);
    free_str_array(init_env_var);
    free_str_array(global_env);

    system("leaks minishell");
    exit(0);
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
//    printf("\n\n================= STR ENV =================\n\n%s\n\n================= STR FIN =================\n\n", str_env);
    write(fd[1], str_env, ft_strlen(str_env));
    //printf("ADRESSE str_env = %p\n", str_env);
    free(str_env);
}

void receipt_env(int *fd)
{
    int ret;
    char buf[101];
    char *str_env;
    char **tab_env;

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
    free(str_env);
    free_str_array(tab_env);
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    (void)env;
    char *line;
    char *cmd;
    char *dir;
    //char **tab_dir;
    char **split_result_1;
    char **split_result_2;
    pid_t child_pid;
    int fd[2];

    //printf("\n\n===========   1   =============\n\n");
//    system("leaks minishell");
    //printf("\n\n============    2   ============\n\n");

    init_env_var = duplicate_array(env, NULL, '=');
    global_env = duplicate_array(env, NULL, '\0');


    //system("leaks minishell");
    //printf("\n\n===========    3    =============\n\n");

    while (1)
    {

        pipe(fd);



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

        /*RECUPERATION INPUT*/
    //    system("leaks minishell");
        get_next_line(0, &line);

        /*TRAITEMENT*/
        if (line && line[0])
        {
            split_result_1 = ft_split(line, ' ');
            cmd = split_result_1[0];
            child_pid = ft_create_child();
            if (child_pid == 0)
            {
                if (ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "env") == 0)
                    ft_builtins(line);
                else
                {
                    if (ft_strcmp(cmd, "cd") == 0)
                        ft_cd(line);
                    else if (ft_strcmp(cmd, "export") == 0)
                        ft_export(line);
                    else if (ft_strcmp(cmd, "unset") == 0)
                        ft_unset(line);
                    else if (ft_strcmp(cmd, "exit") != 0)
                        ft_program(line);
                    send_env(fd);
                }
                return (0);
            }
            else
            {
                wait(NULL);
                if (ft_strcmp(cmd, "exit") == 0)
                    ft_exit(split_result_1);
                if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, ".") == 0)
                    receipt_env(fd);
            }
            free_str_array(split_result_1);
        }
        free(line);
    }
}
