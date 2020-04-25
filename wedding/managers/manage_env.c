/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:46:22 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/06 18:59:49 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

char *read_from_fd(int input_fd[2])
{
    int ret;
    char buf[101];
    char *output_str;
    struct	stat sb;

    fstat(input_fd[0], &sb);
    output_str = NULL;
    if (sb.st_size > 0)
    {
        while ((ret = read(input_fd[0], buf, 100)) > 0)
        {
            buf[ret] = '\0';
            output_str = ft_join(output_str, buf, ft_len(output_str), ft_len(buf));
            if (ret < 100)
                break ;
        }
    }
    return (output_str);
}

char *get_env_value(char *var)
{
    int count;
    char *env_value;
    char **split_result_1;
    char **split_result_2;

    count = 0;
    while (global_env[count])
    {
        split_result_1 = ft_split(global_env[count], '=');
        if (strcmp(split_result_1[0], var) == 0)
        {
            split_result_2 = ft_split(global_env[count], '=');
            env_value = ft_strdup(split_result_2[1]);
            free_str_array(split_result_1);
            free_str_array(split_result_2);
            return (env_value);
        }
        free_str_array(split_result_1);
        count++;
    }
    return (NULL);
}

void send_env(int input_fd[2])
{
    int count;

    count = 0;
    while (global_env[count])
    {
        write(input_fd[1], global_env[count], ft_strlen(global_env[count]));
        write(input_fd[1], "\n", 1);
        count++;
    }
}

void receive_env(int input_fd[2])
{
    int pwd_index;
    char *str_env;
    char **tab_env;
    char **split_result;

    str_env = read_from_fd(input_fd);
    if (str_env)
    {
    tab_env = ft_split(str_env, '\n');
    global_env = duplicate_array(tab_env, global_env, '\0');
    if ((pwd_index = search_in_array(global_env, "PWD", '=')) == -1)
        ft_error('\0', NULL, "PWD not found in environnement variables");
    split_result = ft_split(global_env[search_in_array(global_env, "PWD", '=')], '=');
    chdir(split_result[1]);
    free_str_array(split_result);
    free_str(&str_env);
    free_str_array(tab_env);
    }
}