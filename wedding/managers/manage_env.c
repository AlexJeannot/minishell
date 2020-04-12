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

char *get_env_value(char *var)
{
    int count;

    count = 0;
    while (global_env[count])
    {
        if (strcmp(ft_split(global_env[count], '=')[0], var) == 0)
            return (ft_split(global_env[count], '=')[1]);
        count++;
    }
    return (NULL);
}

int env_need_update(char *cmd)
{
    if ((ft_strcmp(cmd, "export") == 0)
        || (ft_strcmp(cmd, "unset") == 0)
        || (ft_strcmp(cmd, "cd") == 0))
        return (1);
    return (0);
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
    int pwd_index;
    char *str_env;
    char **tab_env;
    char **split_result;

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
    if ((pwd_index = search_in_array(global_env, "PWD", '=')) == -1)
    {
        printf("ERROR PWD NOT FOUND\n");
        exit(1);
    }
    split_result = ft_split(global_env[search_in_array(global_env, "PWD", '=')], '=');
    chdir(split_result[1]);
    free_str_array(split_result);
    free_str(str_env);
    free_str_array(tab_env);
    free_str(piped_str);
}