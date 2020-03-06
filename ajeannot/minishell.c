/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:21:45 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/06 19:00:02 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"


pid_t ft_create_child(void)
{
    pid_t pid;

    pid = fork();
    return (pid);
}

void ft_exit(void)
{
    exit(0);
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    (void)env;
    char *line;
    char *cmd;
    char *dir;
    char **tab_dir;

    init_env_var = duplicate_array(env, '=');
    global_env = duplicate_array(env, '\0');
    while (1)
    {

        /*AFFICHAGE DIR*/
        printf("\033[38;5;208m");
        fflush(stdout);

        tab_dir = ft_split(ft_split(global_env[search_in_array(global_env, "PWD", '=')], '=')[1], '/');
        dir = tab_dir[array_length(tab_dir) - 1];
        write(1, dir, ft_strlen(dir));
        write(1, " ", 1);

        /*AFFICHAGE PROMPT*/
        printf("\033[38;5;196m");
        fflush(stdout);
        write(1, "}> ", 3);
        printf("\033[0m");
        fflush(stdout);

        /*RECUPERATION INPUT*/
        get_next_line(0, &line);
        cmd = ft_split(line, ' ')[0];

        /*TRAITEMENT*/
        if (ft_create_child() == 0)
        {
            if (strcmp(cmd, "pwd") == 0 || strcmp(cmd, "echo") == 0 || strcmp(cmd, "env") == 0)
                ft_path(line, global_env);
            else if (strcmp(cmd, "cd") == 0)
                ft_cd(line);
            else if (strcmp(cmd, "export") == 0)
                ft_export(line);
            else if (strcmp(cmd, "unset") == 0)
                ft_unset(line);
        }
        else
        {
            if (strcmp(cmd, "exit") == 0)
                ft_exit();
            wait(NULL);
        }
    }
}
